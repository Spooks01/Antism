package math;

public class Vec3 {
    public Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }

    public Vec3(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vec3(double x, double y) {
        this.x = (float)x;
        this.y = (float)y;
        this.z = 0.0f;
    }

    public Vec3(Vec2 vec) {
        this.x = vec.x;
        this.y = vec.y;
        this.z = 0.0f;
    }

    public float[] GetData() { return new float[] { this.x, this.y, this.z }; }

    public Vec3 Add(Vec3 other) {
        this.x += other.x;
        this.y += other.y;
        this.z += other.z;

        return this;
    }


    public Vec3 Multiply(Vec3 toMult){
        x *= toMult.x;
        y *= toMult.y;
        z *= toMult.z;
        return this;
    }
    public Vec3 Subtract(Vec3 toSub){
        x -= toSub.x;
        y -= toSub.y;
        z -= toSub.y;
        return this;
    }

    public Vec3 Divide(Vec3 toDiv){
        x /= toDiv.x;
        y /= toDiv.y;
        z /= toDiv.z;
        return this;
    }

    // Variables
    public float x, y, z;
}
