package app;

public class Time {
    // Constructors
    public Time() {
        m_interval = 1;
        m_time = 0;
        m_ticks = 0;
    }

    // Methods
    public void Pause() {

    }

    public void Pause(float delta) {

    }

    public void Resume() {

    }

    public void Update() {
        double delta = System.nanoTime() - m_time;

        // Update ticks
        m_ticks = 1.0f / (delta * 1000.0f);
        m_time = System.nanoTime();
    }

    // Accessors
    public float GetInterval() { return m_interval; }
    public void  SetInterval(float interval) { m_interval = interval; }

    public double GetTime() { return m_time; }

    // Variables
    private float m_interval;
    private double m_time;
    private double m_ticks;
}
