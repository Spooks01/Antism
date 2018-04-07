package graphics;

import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.imageio.ImageIO;

import utils.File;

import static org.lwjgl.opengl.GL11.*;

public class Texture {
    // Constructors
    public Texture(String filepath) { m_id = Load(filepath); }

    private int Load(String filepath) {
        texture = new utils.Image();

        int[] pixels = texture.LoadImage(filepath);

        int result = glGenTextures();

        glBindTexture(GL_TEXTURE_2D, result);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.GetWidth(), texture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, utils.Buffer.CreateIntBuffer(pixels));
        glBindTexture(GL_TEXTURE_2D, 0);

        return result;
    }

    public void Bind() { glBindTexture(GL_TEXTURE_2D, m_id); }
    public void Unbind() {  glBindTexture(GL_TEXTURE_2D, 0); }
    public void Clear(){ glDeleteTextures(m_id); }


    // Variables
    private int m_width, m_height;
    private int m_id;
    private utils.Image texture;
}
