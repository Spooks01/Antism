package environment;

import ant.Ant;

public class Environment {
    // Constructors
    public Environment(int width, int height) {
        m_height = height;
        m_width = width;

        m_grid = new int[height][width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                m_grid[i][j] = 0;
            }
        }
    }
    public Environment(int[][] grid) { m_grid = grid; }

    /** Executed each frame */
    public void Update() {

        // Resets everything to 0
        for (int i = 0; i < m_height ; i++) {
            for (int j = 0; j < m_width; j++) {
                m_grid[i][j] = 0;
            }
        }
    }

    /** Update a cell in the grid */
    public static void UpdateGrid(float x, float y, int value) {
        int width = (int)(x/ Ant.size);
        int height = m_height - (int)(y/ Ant.size) - 1;

        m_grid[height][width] = value;
    }

    // Accessors
    public static int GetWidth() { return m_width; }
    public static int GetHeight() { return m_height; }

    public static int[][] GetGrid() { return m_grid; }
    public static int CheckGrid(float x, float y) {
        int width = (int)(x/ Ant.size);
        int height = m_height - (int)(y/ Ant.size) - 1;

        return m_grid[height][width];
    }

    // Variables
    private static int m_width;
    private static int m_height;
    private static int[][] m_grid;
}
