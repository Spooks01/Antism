package graphics;
import math.Mat4;
import math.Vec3;
import math.Vec4;
import utils.Character;
import utils.TextData;

import java.util.ArrayList;


import static org.lwjgl.opengl.GL11.*;

public class Text extends Drawable {
    private String toDraw;
    private int textH;
    private VertexArray m_vao;
    private IndexBuffer m_ibo;
    int m_width, m_height;

    public Text(String tD, int textHeight, Vec3 pos, Vec4 c){
        toDraw = tD;
        textH = textHeight;
        m_position = pos;
        m_color = c;
        m_shader = new Shader("res/shaders/texture.vert", "res/shaders/texture.frag");
        m_shader.Enable();
        m_shader.SetUniformMat4f("pr_matrix", Mat4.Orthographic(0, Frame.GetWidth(), 0, Frame.GetHeight(), -1.0f, 1.0f));
        m_shader.Disable();
        textSetup();
        genIndexBuffer(toDraw);
    }
    public int[] stringCodes(String S){
        char[] strChars = S.toCharArray();
        int[] codes = new int[strChars.length];
        for (int i = 0; i < strChars.length; i++){
            codes[i] = strChars[i];
        }
        return codes;
    }

    @SuppressWarnings("Duplicates")
    public void Draw(){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        m_shader.Enable();
        TextData.chars.Bind();
        m_vao.Bind();
        m_ibo.Bind();
        glDrawElements(GL_TRIANGLES, m_ibo.GetCount(), GL_UNSIGNED_BYTE, 0);
        m_ibo.Unbind();
        m_vao.Unbind();
        TextData.chars.Unbind();
        m_shader.Disable();
        glDisable(GL_BLEND);
    }

    public void updateText(String newString){
        if (!this.toDraw.equals(newString)) {
            if (toDraw.length() != newString.length()){
                System.out.println("new ibo");
                m_ibo.Clear();
                this.genIndexBuffer(newString);
            }
            this.toDraw = newString;
            m_vao.Clear();
            this.textSetup();
        }
    }

    void genIndexBuffer(String str){
        byte[] indices = new byte[str.length() * 6];
        int offset = 0;

        for (int q = 0; q < (str.length()) * 6; q+=6) {
            indices[ q ] = (byte)(offset + 0);
            indices[q+1] = (byte)(offset + 1);
            indices[q+2] = (byte)(offset + 2);
            indices[q+3] = (byte)(offset + 2);
            indices[q+4] = (byte)(offset + 3);
            indices[q+5] = (byte)(offset + 0);

            offset+=4;
        }
        m_ibo = new IndexBuffer(indices);
    }

    void textSetup(){

        m_vao = new VertexArray();
        float[] fA = new float[12 * toDraw.length()];
        float[] fC = new float[toDraw.length() * 12 * 4];
        for (int z = 0; z < (toDraw.length()) * 12; z+=12){
            fA[z] =  m_position.x + (z/12 * textH/2);
            fA[z + 1] = m_position.y;
            fA[z + 2] = 1.0f;
            fA[z + 3] = m_position.x + (z/12 * textH/2);
            fA[z + 4] =  m_position.y + textH;
            fA[z + 5] = 1.0f;
            fA[z + 6] = m_position.x + (float) (textH*0.5) + (z/12 * textH/2);
            fA[z + 7] = m_position.y + textH;
            fA[z + 8] = 1.0f;
            fA[z + 9] = m_position.x + (float) (textH*0.5) + (z/12 * textH/2);
            fA[z + 10] = m_position.y;
            fA[z + 11]  =  1.0f;

        }
        int[] strCodes = this.stringCodes(toDraw);
        float[] fT = new float[toDraw.length() * 2 * 4];
        for (int kys = 0; kys < (toDraw.length()) * 2 * 4; kys+=8){
            int currCode = strCodes[kys/8];
            int meme = 0;
            while (TextData.charData.get(meme).charCode != currCode){
                meme++;
            }
            float x = TextData.charData.get(meme).x;
            float y = 512 - TextData.charData.get(meme).y;
            //bl
            fT[kys + 2] = (x)/512.f;
            fT[kys + 3] = (y)/512.f;
            //tl
            fT[kys + 0] = (x)/512.f;
            fT[kys + 1] = (y - 32)/512.f;
            //br
            fT[kys + 6] = (x + 32)/512.f;
            fT[kys + 7] = (y - 32)/512.f;
            //tr
            fT[kys + 4] = (x + 32)/512.f;
            fT[kys + 5] = (y)/512.f;
        }

        float[] colors = new float[toDraw.length() * 4 * 4];
        for (int fuckoff = 0; fuckoff < toDraw.length() * 4 * 4; fuckoff+=4){
            colors[fuckoff] = m_color.x;
            colors[fuckoff + 1] = m_color.y;
            colors[fuckoff + 2] = m_color.z;
            colors[fuckoff + 3] = m_color.w;
        }


        m_vao.AddBuffer(new VertexBuffer(fA, 3), 0);
        m_vao.AddBuffer(new VertexBuffer(colors, 4), 1);
        m_vao.AddBuffer(new VertexBuffer(fT, 2), 2);

    }
}
