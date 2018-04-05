package input;

import math.Vec2;
//attach this to a drawable to make it into a button
public class Button  {
    private Vec2[] coords = new Vec2[2];
    private boolean isClicked;
    public Button(Vec2 bL, Vec2 tR){
        coords[0] = bL;
        coords[1] = tR;
    }
    public boolean buttonUpdate(){
        isClicked = false;
        double mouseX = Input.mouseX.get(0);
        double mouseY = Input.mouseY.get(0);

        if (Input.IsMouseButtonPressed(0) && (mouseY < coords[0].y && mouseX > coords[0].x) && (mouseY > coords[1].y && mouseX < coords[1].x)){
            isClicked = true;
        }
        return isClicked;
    }
}
