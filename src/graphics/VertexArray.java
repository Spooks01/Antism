package graphics;

import utils.Buffer;

import java.util.ArrayList;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;

public class VertexArray {
    /** Pure independent constructor */
    public VertexArray() {
        // Generate an unique id in the GPU's memory
        m_id = glGenVertexArrays();
    }

    /** Deletes the buffer from the GPUs memory */
    void Clear() { glDeleteVertexArrays(m_id); }

    /** Binds a VertexBuffer to the specified index in the shader */
    public void AddBuffer(VertexBuffer buffer, int index) {
        Bind();
        buffer.Bind();

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer.GetSize(), GL_FLOAT, false, 0, 0);

        buffer.Unbind();
        Unbind();
    }
    public void AddBuffer(VertexBuffer buffer, int type, boolean normalized, int index) {
        Bind();
        buffer.Bind();

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer.GetSize(), type, normalized, 0, 0);

        buffer.Unbind();
        Unbind();
    }

    // Methods
    /** Binds the VertexArray object into the GPUs memory*/
    public void Bind() { glBindVertexArray(m_id); }
    /** Releases the object from memory */
    public void Unbind() { glBindVertexArray(0); }

    // Variables
    private int m_id;
}
