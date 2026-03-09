#ifndef SSO_TIMER_H
#define SSO_TIMER_H

#include <chrono>

namespace SSO {
    /**
     * @brief Universal Time Management System for SSOEngine.
     * Provides high-precision Delta Time and flexible game timers.
     */
    class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
        float m_CurrentValue = 0.0f;
        bool m_IsActive = false;

    public:
        Timer() {
            m_StartTime = std::chrono::high_resolution_clock::now();
            m_LastTime = m_StartTime;
        }

        // --- Core Engine Timing ---
        
        /**
         * @return Frame duration in seconds (Delta Time).
         */
        float GetDeltaTime() {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
            m_LastTime = currentTime;
            return deltaTime;
        }

        /**
         * @return Total time elapsed since the application started.
         */
        float GetTotalTime() const {
            auto currentTime = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<float>(currentTime - m_StartTime).count();
        }

        // --- Flexible Gameplay Timing ---

        void SetValue(float value) { m_CurrentValue = value; }
        float GetValue() const { return m_CurrentValue; }
        
        void Start() { m_IsActive = true; }
        void Stop()  { m_IsActive = false; }
        void Reset() { m_CurrentValue = 0.0f; m_IsActive = false; }

        /**
         * @brief Logic for Countdown (Waktu Mundur)
         */
        void UpdateCountdown(float dt) {
            if (m_IsActive && m_CurrentValue > 0) m_CurrentValue -= dt;
            if (m_CurrentValue < 0) { m_CurrentValue = 0; m_IsActive = false; }
        }

        /**
         * @brief Logic for Stopwatch (Waktu Maju)
         */
        void UpdateStopwatch(float dt) {
            if (m_IsActive) m_CurrentValue += dt;
        }

        bool IsFinished() const { return m_CurrentValue <= 0 && !m_IsActive; }
        bool IsRunning() const { return m_IsActive; }
    };
}

#endif