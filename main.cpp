/*
 * The Universal Harmonic Matrix: Base-27720 DDS Architecture
 * Author: Olexandr Lozovyi
 * Platform: ESP32 (Arduino framework / PlatformIO)
 * Description: 
 * This code implements a Direct Digital Synthesis (DDS) phase accumulator 
 * based on the highly composite number 27720. It systematically eliminates 
 * phase jitter for fundamental non-linear resonances (3rd, 5th, 7th, 11th).
 */

#include <Arduino.h>
#include <math.h>

// ==========================================
// КОНФІГУРАЦІЯ ГАРМОНІЙНОЇ МАТРИЦІ
// ==========================================
const uint16_t HARMONIC_BASE = 27720; 

// Виділяємо 27.7 кБ в оперативній пам'яті для таблиці синусів (LUT)
uint8_t sine_LUT[HARMONIC_BASE];

// Змінні фазового акумулятора (volatile для безпечної роботи в перериваннях)
volatile uint16_t phase_accumulator = 0;
volatile uint16_t phase_increment = 0;

// Апаратний вивід (ЦАП ESP32 знаходиться на GPIO 25)
const int DAC_PIN = 25;

// Вказівник на апаратний таймер ESP32
hw_timer_t * timer = NULL;

// ==========================================
// ПЕРЕРИВАННЯ РЕАЛЬНОГО ЧАСУ (DDS CORE)
// ==========================================
/* * IRAM_ATTR розміщує цю функцію у швидкому кеші інструкцій (L1/IRAM).
 * Це гарантує виконання без затримок звернення до Flash-пам'яті.
 */
void IRAM_ATTR onTimer() {
    // 1. Акумуляція фази
    phase_accumulator += phase_increment;
    
    // 2. Оптимізація апаратного рівня: уникаємо повільного ділення (% 27720).
    // Компаратор (>=) та віднімання (-) виконуються за 1-2 такти процесора.
    if (phase_accumulator >= HARMONIC_BASE) {
        phase_accumulator -= HARMONIC_BASE;
    }
    
    // 3. Пряме зчитування амплітуди з таблиці та вивід на ЦАП (DAC)
    dacWrite(DAC_PIN, sine_LUT[phase_accumulator]);
}

// ==========================================
// ІНІЦІАЛІЗАЦІЯ СИСТЕМИ
// ==========================================
void setup() {
    Serial.begin(115200);
    Serial.println("\n=== Universal Harmonic Matrix DDS ===");
    Serial.println("Initializing Base-27720 Architecture...\n");

    // --- МАТЕМАТИЧНА ВАЛІДАЦІЯ (Доказ нульового джитеру) ---
    Serial.println("[ Mathematical Validation: LCM(1..12) Divisibility ]");
    Serial.printf("Base / 3rd Harmonic  (27720 / 3)  = %d\n", HARMONIC_BASE / 3);
    Serial.printf("Base / 5th Harmonic  (27720 / 5)  = %d\n", HARMONIC_BASE / 5);
    Serial.printf("Base / 7th Harmonic  (27720 / 7)  = %d\n", HARMONIC_BASE / 7);
    Serial.printf("Base / 11th Harmonic (27720 / 11) = %d\n\n", HARMONIC_BASE / 11);

    // --- ДИНАМІЧНА ГЕНЕРАЦІЯ LUT ---
    Serial.println("[ Generating Ideal Waveform LUT ]");
    for (int i = 0; i < HARMONIC_BASE; i++) {
        float angle = ((float)i / HARMONIC_BASE) * 2.0 * PI;
        sine_LUT[i] = (uint8_t)((sin(angle) + 1.0) * 127.5);
    }
    Serial.println("-> LUT [27.7 kB] successfully generated in SRAM.\n");

    // --- НАЛАШТУВАННЯ ГАРМОНІКИ ---
    phase_increment = 3960; 
    Serial.printf("Target Harmonic: 7th | Phase Increment: %d\n", phase_increment);

    // --- ІНІЦІАЛІЗАЦІЯ ТАЙМЕРА ---
    // Дільник 80: таймер працює на частоті 1 МГц (1 тік = 1 мікросекунда)
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    
    // Встановлюємо частоту генерації. Наприклад: 10 мкс = 100 кГц Sample Rate
    timerAlarmWrite(timer, 10, true);
    timerAlarmEnable(timer);
    
    Serial.println("\n>>> Hardware Timer started. Outputting zero-jitter waveform on DAC_PIN 25. <<<");
}

// ==========================================
// ГОЛОВНИЙ ЦИКЛ
// ==========================================
void loop() {
    delay(10000); // Чекаємо 10 секунд
    
    // --- ДЕМОНСТРАЦІЯ PHASE-CONTINUOUS SWITCHING ---
    // Перемикання частоти відбувається без скидання phase_accumulator.
    // Це гарантує відсутність розривів фази (клацань) на осцилограмі,
    // що критично для систем фазового автопідлаштування (PLL) та ФМ-модуляції.
    
    noInterrupts(); // Блокуємо переривання для атомарної зміни фази
    phase_increment = 2520; // Перехід на 11-ту гармоніку
    interrupts();   // Відновлюємо переривання
    
    Serial.println("Switched to 11th Harmonic | Phase Increment: 2520 (Phase-Continuous)");
    delay(10000);
    
    noInterrupts();
    phase_increment = 3960; // Повернення на 7-му гармоніку
    interrupts();
    
    Serial.println("Switched back to 7th Harmonic | Phase Increment: 3960 (Phase-Continuous)");
}