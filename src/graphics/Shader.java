package graphics;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL20.*;

import math.Mat4;
import utils.File;

import java.util.HashMap;
import java.util.Map;

public class Shader {
    /** Default Shader constructor, loads in base shader files */
    public Shader() { m_id = Load("res/shaders/base.vert", "res/shaders/base.frag"); }
    /** Compiles the shader from the given filenames into m_id */
    public Shader(String vertexpath, String fragmentpath) { m_id = Load(vertexpath, fragmentpath); }

    /** Loads shader data from the specified file paths */
    int Load(String vertexpath, String fragmentpath) {
        String vertex = File.LoadAsString(vertexpath);
        String fragment = File.LoadAsString(fragmentpath);

        int program = glCreateProgram();
        int vertid = glCreateShader(GL_VERTEX_SHADER);
        int fragid = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertid, vertex);
        glShaderSource(fragid, fragment);

        glCompileShader(vertid);
        if (glGetShaderi(vertid, GL_COMPILE_STATUS) == GL_FALSE) {
            System.err.println("Failed to compiled Vertex Shader.");
            System.err.println(glGetShaderInfoLog(vertid));
            return -1;
        }
        glCompileShader(fragid);
        if (glGetShaderi(fragid, GL_COMPILE_STATUS) == GL_FALSE) {
            System.err.println("Failed to compiled Fragment Shader.");
            System.err.println(glGetShaderInfoLog(fragid));
            return -1;
        }

        glAttachShader(program, vertid);
        glAttachShader(program, fragid);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertid);
        glDeleteShader(fragid);

        return program;
    }

    // Accessors
    /** Assign an int value to corresponding uniform inside the shader */
    public void SetUniform1i(String name, int value) { glUniform1i(GetUniformLocation(name), value); }
    /** Assign a float value to corresponding uniform inside the shader */
    public void SetUniform1f(String name, float value) { glUniform1f(GetUniformLocation(name), value); }
    /** Assign a 2 dimensional array to corresponding uniform inside the shader */
    public void SetUniform2fv(String name, float[] value) { glUniform2fv(GetUniformLocation(name), value); }
    /** Assign a 3 dimensional array to corresponding uniform inside the shader */
    public void SetUniform3fv(String name, float[] value) { glUniform3fv(GetUniformLocation(name), value); }
    /** Assign a 4 dimensional array to corresponding uniform inside the shader*/
    public void SetUniform4fv(String name, float[] value) { glUniform4f(GetUniformLocation(name), value[0], value[1], value[2], value[3]); }
    /** Assign a matrix array to a corresponding uniform inside the shader */
    public void SetUniformMat4f(String name, float[] value) { glUniformMatrix4fv(GetUniformLocation(name), false, value); }
    public void SetUniformMat4f(String name, Mat4 matrix) { glUniformMatrix4fv(GetUniformLocation(name), false, matrix.GetData()); }

    // Methods
    /** Tell OpenGL to use the shader program id */
    public void Enable() { glUseProgram(m_id); }
    /** Reset the program id inside OpenGL's buffer */
    public void Disable() { glUseProgram(0); }
    public void Clear(){glDeleteShader(m_id);}
    /** Retrieves the uniform location id based on name
     *  Each unique name is cached into a HashMap, as glGetUniformLocation is extremely expensive */
    private int GetUniformLocation(String name) {
        if (m_cache.containsKey(name))
            return m_cache.get(name);

        int result = glGetUniformLocation(m_id, name);
        if (result == -1)
            System.err.println("Couldn't find uniform location.");
        else
            m_cache.put(name, result);

        return result;
    }

    // Variables
    /** Id of the compiled shader program */
    private int m_id;
    /** Buffer to hold uniform locations */
    private Map<String, Integer> m_cache = new HashMap<String, Integer>();
}
