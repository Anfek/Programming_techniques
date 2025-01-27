public class Complex {
    public double complex_x, complex_iy;

    public Complex() {}

    public Complex(double x, double y) {
        complex_x = x;
        complex_iy = y;
    }

    public double Mod_z(double complex_x, double complex_iy) {
        return Math.sqrt(Math.pow(complex_x, 2) + Math.pow(complex_iy, 2));
    }

    public double Arg_z(double complex_x, double complex_iy) {
        if (complex_x > 0)
            return Math.atan(complex_iy / complex_x);
        else if (complex_x < 0) {
            if (complex_iy < 0)
                return -Math.PI + Math.atan(complex_iy / complex_x);
            else
                return Math.PI + Math.atan(complex_iy / complex_x);
        } 
        else /*if (complex_x == 0)*/ {
            if (complex_iy > 0)
                return Math.PI / 2;
            else if (complex_iy < 0)
                return -Math.PI / 2;
            else
                return -100;
        }
    }

    public String Sum_or_Dif_Complex_numbs(double x1, double y1, double x2, double y2, char operation) {
        double x, y;
        switch (operation){
            case '+':
                x = x1 + x2;
                y = y1 + y2;
                break;
            case '-':
                x = x1 - x2;
                y = y1 - y2;
                break;
            default:
              return "error";
        }
        if (y >= 0)
            return x+"+"+y+"i";
        else 
            return x+"-"+Math.abs(y)+"i";
        
    }
}