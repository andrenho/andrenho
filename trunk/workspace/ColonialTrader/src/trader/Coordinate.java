package trader;

public class Coordinate {

        @Override
        public int hashCode() {
                return x*1000 + y;
        }

        @Override
        public boolean equals(Object o) {
                if(!(o instanceof Coordinate))
                        return false;
                return (((Coordinate)o).x == this.x && ((Coordinate)o).y == this.y);
        }

        public int x;
        public int y;

        public Coordinate()
        {
                this.x = this.y = 0;
        }

        public Coordinate(int x, int y)
        {
                this.x = x;
                this.y = y;
        }

        public boolean near(Coordinate c)
        {
                return (Math.abs(this.x - c.x) <= 1 && Math.abs(this.y - c.y) <= 1);
        }
}