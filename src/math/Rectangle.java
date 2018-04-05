package math;

public class Rectangle {
    public Rectangle() {
        x = 0;
        y = 0;
        width = 1;
        height = 1;
    }

    public Rectangle(int left, int top, int right, int bottom) {
        x = left;
        y = bottom;
        width = right - left;
        height = top - bottom;
    }

    public Rectangle(float x, float y, float width, float height) {
        this.x = (int)x;
        this.y = (int)y;
        this.width = (int)width;
        this.height = (int)height;
    }

    public boolean Intersects(Rectangle rect) {
        // Checks if any corners are within the parent rectangle
        return (Contains(new Vec2(rect.x, rect.y)) ||
                Contains(new Vec2(rect.x + width, rect.y)) ||
                Contains(new Vec2(rect.x + width, rect.y + height)) ||
                Contains(new Vec2(rect.x, rect.y + height)));
    }

    public boolean Contains(Vec2 point) {
        if (point.x <= x + width && point.x >= x)
            if (point.y <= y + height && point.y >= y)
                return true;

        return false;
    }

    // Variables
    public int x, y;
    public int width, height;
}
