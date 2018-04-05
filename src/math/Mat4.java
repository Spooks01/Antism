package math;

import java.lang.Math;

public class Mat4 {
    // Constructors
    public Mat4(){
        for(int i = 0; i < 16; i++){
            m_elements[i] = 0.0f;
        }

        m_elements[0] = 1.0f;
        m_elements[5] = 1.0f;
        m_elements[10] = 1.0f;
        m_elements[15] = 1.0f;
    }

    public Mat4(float[] array){
        m_elements = array;
    }
    
    private static Mat4 Identity(){
        Mat4 identity = new Mat4();
        for(int i = 0; i < 16; i++){
            identity.m_elements[i] = 0.0f;
        }
        
        identity.m_elements[0] = 1.0f;
        identity.m_elements[5] = 1.0f;
        identity.m_elements[10] = 1.0f;
        identity.m_elements[15] = 1.0f;
        
        return identity;
    }

    public Mat4 Multiply(Mat4 other){
        Mat4 result = new Mat4();
        //1st column
        result.m_elements[0] = this.m_elements[0] * other.m_elements[0] + this.m_elements[1] * other.m_elements[4] + this.m_elements[2] * other.m_elements[8] + this.m_elements[3] * other.m_elements[12];
        result.m_elements[4] = this.m_elements[4] * other.m_elements[0] + this.m_elements[5] * other.m_elements[4] + this.m_elements[6] * other.m_elements[8] + this.m_elements[7] * other.m_elements[12];
        result.m_elements[8] = this.m_elements[8] * other.m_elements[0] + this.m_elements[9] * other.m_elements[4] + this.m_elements[10] * other.m_elements[8] + this.m_elements[11] * other.m_elements[12];
        result.m_elements[12] = this.m_elements[12] * other.m_elements[0] + this.m_elements[13] * other.m_elements[4] + this.m_elements[14] * other.m_elements[8] + this.m_elements[15] * other.m_elements[12];
        //second column
        result.m_elements[1] = this.m_elements[0] * other.m_elements[1] + this.m_elements[1] * other.m_elements[5] + this.m_elements[2] * other.m_elements[9] + this.m_elements[3] * other.m_elements[13];
        result.m_elements[5] = this.m_elements[4] * other.m_elements[1] + this.m_elements[5] * other.m_elements[5] + this.m_elements[6] * other.m_elements[9] + this.m_elements[7] * other.m_elements[13];
        result.m_elements[9] = this.m_elements[8] * other.m_elements[1] + this.m_elements[9] * other.m_elements[5] + this.m_elements[10] * other.m_elements[9] + this.m_elements[11] * other.m_elements[13];
        result.m_elements[13] = this.m_elements[12] * other.m_elements[1] + this.m_elements[13] * other.m_elements[5] + this.m_elements[14] * other.m_elements[9] + this.m_elements[15] * other.m_elements[13];
        //third
        result.m_elements[2] = this.m_elements[0] * other.m_elements[2] + this.m_elements[1] * other.m_elements[6] + this.m_elements[2] * other.m_elements[10] + this.m_elements[3] * other.m_elements[14];
        result.m_elements[6] = this.m_elements[4] * other.m_elements[2] + this.m_elements[5] * other.m_elements[6] + this.m_elements[6] * other.m_elements[10] + this.m_elements[7] * other.m_elements[14];
        result.m_elements[10] = this.m_elements[8] * other.m_elements[2] + this.m_elements[9] * other.m_elements[6] + this.m_elements[10] * other.m_elements[10] + this.m_elements[11] * other.m_elements[14];
        result.m_elements[14] = this.m_elements[12] * other.m_elements[2] + this.m_elements[13] * other.m_elements[6] + this.m_elements[14] * other.m_elements[10] + this.m_elements[15] * other.m_elements[14];
        //fourth
        result.m_elements[3] = this.m_elements[0] * other.m_elements[3] + this.m_elements[1] * other.m_elements[7] + this.m_elements[2] * other.m_elements[11] + this.m_elements[3] * other.m_elements[15];
        result.m_elements[7] = this.m_elements[4] * other.m_elements[3] + this.m_elements[5] * other.m_elements[7] + this.m_elements[6] * other.m_elements[11] + this.m_elements[7] * other.m_elements[15];
        result.m_elements[11] = this.m_elements[8] * other.m_elements[3] + this.m_elements[9] * other.m_elements[7] + this.m_elements[10] * other.m_elements[11] + this.m_elements[11] * other.m_elements[15];
        result.m_elements[15] = this.m_elements[12] * other.m_elements[3] + this.m_elements[13] * other.m_elements[7] + this.m_elements[14] * other.m_elements[11] + this.m_elements[15] * other.m_elements[15];

        return result;
    }

    public static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) {
        Mat4 result = new Mat4();
        
        result.m_elements[0 + 0 * 4] = 2.0f / (right - left);
        result.m_elements[1 + 1 * 4] = 2.0f / (top - bottom);
        result.m_elements[2 + 2 * 4] = 2.0f / (near - far);
        result.m_elements[0 + 3 * 4] = (left + right) / (left - right);
        result.m_elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
        result.m_elements[2 + 3 * 4] = (far + near) / (far - near);
        
        return result;
    }

    public static Mat4 Rotate(float angle){
        Mat4 result = new Mat4();
        
        result.m_elements[0] = (float) Math.cos(Math.toRadians(angle));
        result.m_elements[1] = (float) -Math.sin(Math.toRadians(angle));
        result.m_elements[4] = (float) Math.sin(Math.toRadians(angle));
        result.m_elements[5] = (float) Math.cos(Math.toRadians(angle));

        return result;
    }

    //return a translated matrix
    public static Mat4 Translate(float x, float y, float z) {
        Mat4 translation = new Mat4();
        
        translation.m_elements[12] = x;
        translation.m_elements[13] = y;
        translation.m_elements[14] = z;
        
        return translation;
    }

    public static Mat4 Translate(Vec3 position) {
        Mat4 translation = new Mat4();
        
        translation.m_elements[12] = position.x;
        translation.m_elements[13] = position.y;
        translation.m_elements[14] = position.z;
        
        return translation;
    }

    public Mat4 Transpose(){
        Mat4 result = new Mat4();
        //1st column
        result.m_elements[0] = this.m_elements[0];
        result.m_elements[4] = this.m_elements[1];
        result.m_elements[8] = this.m_elements[2];
        result.m_elements[12] = this.m_elements[3];
        //you know how this works
        result.m_elements[1] = this.m_elements[4];
        result.m_elements[5] = this.m_elements[5];
        result.m_elements[9] = this.m_elements[6];
        result.m_elements[13] = this.m_elements[7];
        //
        result.m_elements[2] = this.m_elements[8];
        result.m_elements[6] = this.m_elements[9];
        result.m_elements[10] = this.m_elements[10];
        result.m_elements[14] = this.m_elements[11];
        //
        result.m_elements[3] = this.m_elements[12];
        result.m_elements[7] = this.m_elements[13];
        result.m_elements[11] = this.m_elements[14];
        result.m_elements[15] = this.m_elements[15];
        
        return result;
    }
    
    public float[] GetData() { return m_elements; }
    
    // Variables
    //contains the matrix elements
    private float[] m_elements = new float[16];
}
