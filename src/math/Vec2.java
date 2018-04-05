package math;

public class Vec2 {
    public Vec2() {
        x = 0;
        y = 0;
    }

    public Vec2(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Vec2(double x, double y) {
        this.x = (float)x;
        this.y = (float)y;
    }

    public float[] GetData() { return new float[] { this.x, this.y }; }

    public Vec2 Add(Vec2 toAdd){
        x += toAdd.x;
        y += toAdd.y;
        return this;
    }

    public Vec2 Multiply(Vec2 toMult){
        x *= toMult.x;
        y *= toMult.y;
        return this;
    }
    public Vec2 Subtract(Vec2 toSub){
        x -= toSub.x;
        y -= toSub.y;
        return this;
    }

    public Vec2 Divide(Vec2 toDiv){
        x /= toDiv.x;
        y /= toDiv.y;
        return this;
    }

    // Variables
    public float x, y;
}
