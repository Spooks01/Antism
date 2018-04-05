package graphics;

import utils.Buffer;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;

public class IndexBuffer {
    // Constructors
    public IndexBuffer(byte[] indices) {
        // Generate an unique id in the GPU's memory
        m_id = glGenBuffers();
        m_count = indices.length;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Buffer.CreateByteBuffer(indices), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /** Deletes the buffer from the GPUs memory */
    void Clear() { glDeleteBuffers(m_id); }

    // Accessors
    /** Returns the amount of indices in the buffer */
    public int GetCount() { return m_count; }
    // Methods
    /** Binds the id of the buffer to the GL_ARRAY_BUFFER target for rendering */
    public void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
    /** Clears the GL_ARRAY_BUFFER buffer */
    public void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    // Variables
    private int m_id;
    private int m_count;
}
