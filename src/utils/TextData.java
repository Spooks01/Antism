package utils;

import graphics.Texture;

import java.util.ArrayList;

public class TextData {

    public static Texture chars = new Texture("res/font/calibri.png");
    public static ArrayList<Character> charData;
    public static void setup(){
        charData = new ArrayList<>();
        int code = 32;
        for (int y = 0; y < 14; y++){
            for (int x = 0; x < 16; x++){
                charData.add(new Character(y * 32, x * 32, code));
                code++;
            }
        }
    }

}
