package environment;

import graphics.Square;
import math.Vec3;
import math.Vec4;

public class Food extends Square {
    // Constructors
    public Food() {
        super(8);

        m_amount = 1;
        m_decay = 1;

        SetColor(new Vec3(0, 1, 0));
    }

    // Accessors
    public int GetAmount() { return m_amount; }
    public void SetAmount(int amount) { m_amount = amount; }

    public float GetDecayRate() { return m_decay; }
    public void SetDecayRate(float rate) { m_decay = rate; }

    // Variables
    private int m_amount;
    private float m_decay;
}
