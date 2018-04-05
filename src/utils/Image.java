package utils;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Image{
    // Constructors
    public int[] LoadImage(String filepath) {
        int[] pixels = null;
        try {
            BufferedImage image = ImageIO.read(new FileInputStream(filepath));
            m_width = image.getWidth();
            m_height = image.getHeight();
            pixels = new int[m_width * m_height];
            image.getRGB(0, 0, m_width, m_height, pixels, 0, m_width);
        } catch (IOException e) {
            e.printStackTrace();
        }

        m_data = new int[m_width * m_height];
        for (int i = 0; i < m_width * m_height; i++) {
            int a = (pixels[i] & 0xff000000) >> 24;
            int r = (pixels[i] & 0xff0000) >> 16;
            int g = (pixels[i] & 0xff00) >> 8;
            int b = (pixels[i] & 0xff);

            m_data[i] = a << 24 | b << 16 | g << 8 | r;
        }
        return m_data;
    }

    // Accessors
    public int GetWidth(){ return m_width; }
    public int GetHeight(){ return m_height; }
    public int[] GetData() { return m_data; }

    // Static Methods
    public static byte[] ImageToByteArray(String filepath) {
        byte[] m_data;
        int m_width = 0;
        int m_height = 0;
        int[] pixels = null;
        try {
            BufferedImage image = ImageIO.read(new FileInputStream(filepath));
            m_width = image.getWidth();
            m_height = image.getHeight();
            pixels = new int[m_width * m_height];
            image.getRGB(0, 0, m_width, m_height, pixels, 0, m_width);
        } catch (IOException e) {
            e.printStackTrace();
        }

        m_data = new byte[m_width * m_height * 4];
        for (int i = 0; i < m_width * m_height * 4; i+= 4) {
            m_data[i] = (byte)((pixels[i/4] & 0xff0000) >> 16);
            m_data[i + 1] = (byte)((pixels[i/4] & 0xff00) >> 8);
            m_data[i + 2] = (byte)(pixels[i/4] & 0xff);
            m_data[i + 3] = (byte)((pixels[i/4] & 0xff000000) >> 24);
        }
        return m_data;
    }

    // Variables
    private int m_width, m_height;
    private int[] m_data;
}