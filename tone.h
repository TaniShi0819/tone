#ifndef TONE_H
#define TONE_H


#include "mbed.h"

    /** 
     * @brief 音を鳴らすことができます
     * @param PWM_PIN ピン(PWMのみ)
     * @param FREQUENCY 音の周波数(Hz)
     * @param DURATION 音の長さ(ms)
     * @attention 音を鳴らしている最中はほかの処理ができないので注意
     * @note PWM_PINにFREQUENCYの高さの音が出るようDURATION間電圧をPWM信号でかけます
     */
    void tone(PwmOut &PWM_PIN, float FREQUENCY, int DURATION)
    {
        if (DURATION == 0)
        {
            PWM_PIN.period(1.0 / FREQUENCY);
            PWM_PIN.write(0.5);
        }
        else
        {
            PWM_PIN.period(1.0 / FREQUENCY);
            PWM_PIN.write(0.5);
            ThisThread::sleep_for(DURATION);
            PWM_PIN.write(0.0);
        }
    }

    /** 
     * @brief 音を消します
     * @param PWM_PIN ピン(PWMのみ)
     * @param DURATION 無音の長さ(ms)
     * @attention 音を鳴らしている最中はほかの処理ができないので注意
     * @note PWM_PINにDURATION間電圧を流しません
     */
    void notone(PwmOut &PWM_PIN, int DURATION)
    {
        if (DURATION == 0)
        {
            PWM_PIN.write(0.0);
        }
        else
        {
            ThisThread::sleep_for(DURATION);
            PWM_PIN.write(0.0);
        }
    }

    /** 
     * @brief sシャトルランの音源を再生します
     * @param PWM_PIN ピン(PWMのみ)
     * @param LOOP 繰り返しの回数
     * @attention 音を鳴らしている最中はほかの処理ができないので注意
     * @note シャトルランのようにだんだんと音の長さと間隔が短くなるように音階を鳴らします
     */
    void playShuttleRun(PwmOut &PWM_PIN, int LOOP)
    {
        int melody[8] = {
        262, // ド (C4)
        294, // レ (D4)
        330, // ミ (E4)
        349, // ファ (F4)
        392, // ソ (G4)
        440, // ラ (A4)
        494, // シ (B4)
        523, // ド (C5)
        };

    int decreaseAmount = 50;     // 各ステージごとに減少する間隔（50ミリ秒）
    int DURATION = 800;          // 最初の音の長さ）

    int interval = 1000;

        for (int stage = 1; stage <= LOOP; stage++) {
            // メロディを再生
            for (int i = 0; i < 8; i++) {
            tone(PWM_PIN, melody[i], DURATION); // 各音を鳴らす
            notone(PWM_PIN, DURATION/2);
            }

            tone(PWM_PIN, melody[0], DURATION);
            notone(PWM_PIN, DURATION/2);

            for (int i = 7; i >= 0; i--) {
            tone(PWM_PIN, melody[i], DURATION); // 各音を鳴らす
            notone(PWM_PIN, DURATION/2);
            }

            tone(PWM_PIN, melody[0], DURATION);
            notone(PWM_PIN, DURATION/2);
            
            // 次のステージのために音の間隔を短くする
            DURATION -= decreaseAmount;
            interval -= decreaseAmount;
        }
    }

#endif