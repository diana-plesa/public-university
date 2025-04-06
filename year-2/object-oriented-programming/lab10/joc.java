import java.util.Random;
import java.util.Date;

class Joc
{
    private String echipa1;
    private String echipa2;
    private int goluri1 = 0;
    private int goluri2 = 0;
    private int outs = 0;
    private int corners = 0;

    public Joc(String n1, String n2)
    {
	echipa1 = n1;
	echipa2 = n2;
    }

    public String getEchipa1()
    {
	return echipa1;
    }

    public String getEchipa2()
    {
	return echipa2;
    }

    public void golEchipa1()
    {
	goluri1++;
    }

    public void golEchipa2()
    {
	goluri2++;
    }

    public void addCorner()
    {
	corners++;
    }

    public void addOut()
    {
	outs++;
    }
    

    public String toString()
    {
	String str = echipa1 + ": " + goluri1 + " | " + echipa2 + ": " + goluri2 + " Outs: " + outs + " Corners: " + corners;
	return str;
    }

    public void simuleaza()
    {
	Minge m = new Minge(50, 25);
	
	for (int i = 0; i < 1000; i++)
	    {
		try
		    {
			m.suteaza();
			
		    }
		
		catch (GolException gol)
		    {
			System.out.println(gol.getMessage() + " - X: " + m.getX() + " Y: " + m.getY());
			
			if (m.getX() == 0)
			    golEchipa1();
			
			if (m.getX() == 100)
			    golEchipa2();
			
			m = new Minge(50, 25);
		    }
		
		catch (OutException out)
		    {
			System.out.println(out.getMessage());
			
			m = new Minge(m.getX(), m.getY());
			addOut();	
		    }
		
		catch (CornerException corner)
		    {
			System.out.println(corner.getMessage());
			
			m = new Minge(m.getX(), m.getY());
			addCorner();
		    }
		
		catch(Exception ex)
		    {
			System.out.println("Found Exception");
		    }
		
		finally
		    {
			System.out.println(echipa1 + " - " +echipa2 + ": Mingea se afla la coordonatele (" + m.getX() + " " + m.getY() + ")");
			
		    }
	    }
	        System.out.println(toString());
		System.out.println("Game over");
	    
    }
    


    public static void main(String args[])
    {
	Joc j = new Joc("Rosu", "Albastru");
	j.simuleaza();
	    
    }
    
}

class Minge
{
    private int x, y;
    private Random randomGenerator;
    
    public Minge(int x, int y)
    {
	this.x = x;
	this.y = y;

	Date now = new Date();
	long sec = now.getTime();
	randomGenerator = new Random(sec);
    }

    public int getX()
    {
	return x;
    }

    public int getY()
    {
	return y;
    }

    public void getCoord()
    {
	System.out.println("X: " + x);
	System.out.println("Y: " + y);
    }

    public void suteaza() throws OutException, GolException, CornerException
    {
	x = randomGenerator.nextInt(101);
	y = randomGenerator.nextInt(101);

	if (x > 95) x = 100;
	if (x < 5) x = 0;

	if (y > 95) y = 100;
	if (y < 5) y = 0;

	if (y == 0 || y == 50)
	    {
		throw new OutException("Out");
	    }

	if ((x == 0 || x == 100) && (y >= 20 && y <= 30))
	    {
		throw new GolException("Gol");
	    }

	if ((x == 0 || x == 100) && ( y > 0 && y < 20 || y > 30 && y < 50))
	    {
		throw new CornerException("Corner");
	    }
    }
	
}

class OutException extends Exception
{
    public OutException(String msg)
    {
	super(msg);
    }
}

class GolException extends Exception
{
    public GolException(String msg)
    {
	super(msg);
    }
}

class CornerException extends Exception
{
    public CornerException(String msg)
    {
	super(msg);
    }
}

