package math;

public class Vec4 {
    public Vec4() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    public Vec4(float x, float y, float z, float w) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
    }

    public Vec4(double x, double y) {
        this.x = (float)x;
        this.y = (float)y;
        this.z = 1.0f;
        this.w = 1.0f;
    }

    public float[] GetData() { return new float[] { this.x, this.y, this.z, this.w }; }

    public Vec4 Add(Vec4 toAdd){
        x += toAdd.x;
        y += toAdd.y;
        z += toAdd.z;
        w += toAdd.w;
        return this;
    }

    public Vec4 Multiply(Vec4 toMult){
        x *= toMult.x;
        y *= toMult.y;
        z *= toMult.z;
        w *= toMult.w;
        return this;
    }
    public Vec4 Subtract(Vec4 toSub){
        x -= toSub.x;
        y -= toSub.y;
        z -= toSub.y;
        w -= toSub.w;
        return this;
    }

    public Vec4 Divide(Vec4 toDiv){
        x /= toDiv.x;
        y /= toDiv.y;
        z /= toDiv.z;
        w /= toDiv.w;
        return this;
    }

    // Variables
    public float x, y, z, w;
}
