class Main
{
    public static void main(String args[])
    {
	ColectieGreutati colectie = new ColectieGreutati(6);

	GreutateSimpla gSimpla1 = new GreutateSimpla(2);
	GreutateSimpla gSimpla2 = new GreutateSimpla(4);
      	GreutateSimpla gSimpla3 = new GreutateSimpla(2);
	GreutateSimpla gSimpla4 = new GreutateSimpla(1);
       	GreutateSimpla gSimpla5 = new GreutateSimpla(6);
	GreutateSimpla gSimpla6 = new GreutateSimpla(5);

	GreutateDubla gDub1 = new GreutateDubla(gSimpla3, gSimpla4);
	GreutateDubla gDub2 = new GreutateDubla(gSimpla5, gSimpla6);
	
	Greutate[] gMul1 = new Greutate[3];
	Greutate[] gMul2 = new Greutate[3];
	
	gMul1[0] = new GreutateSimpla(3);
	gMul1[1] = new GreutateSimpla(6);
	GreutateSimpla g1 = new GreutateSimpla(3);
	GreutateSimpla g2 = new GreutateSimpla(2);
	gMul1[2] = new GreutateDubla(g1, g2);

	gMul2[0] = new GreutateSimpla(5);
	gMul2[1] = new GreutateSimpla(2);
	gMul2[2] = new GreutateSimpla(4);
	
	GreutateMultipla multipla1 = new GreutateMultipla(gMul1);
	GreutateMultipla multipla2 = new GreutateMultipla(gMul2);

	colectie.adauga(gSimpla1);
	colectie.adauga(gSimpla2);
	colectie.adauga(gDub1);
	colectie.adauga(gDub2);
	colectie.adauga(multipla1);
	colectie.adauga(multipla2);

	System.out.println(colectie.medie());
	
    }
}

abstract class Greutate
{
    abstract public int capacitate();
}

class GreutateSimpla extends Greutate
{
    private int capacitate;

    public GreutateSimpla(int capacitate)
    {
	this.capacitate = capacitate;
    }

    public int capacitate()
    {
	return capacitate;
    }
}

class GreutateDubla extends Greutate
{
    private Greutate g1, g2;


    public GreutateDubla(Greutate g1, Greutate g2)
    {
	this.g1 = g1;
	this.g2 = g2;
    }

    public void setGreutate1(Greutate g)
    {
	this.g1 = g;
    }

    public void setGreutate2(Greutate g)
    {
	this.g2 = g;
    }

    public int capacitate()
    {
	int capacitate = g1.capacitate() + g2.capacitate();
	return capacitate;
    }
}

class GreutateMultipla extends Greutate
{
    private Greutate greutate[] = new Greutate[3];

    public GreutateMultipla(Greutate[] g)
    {
	greutate = g;
    }

    public int capacitate()
    {
	int capacitate = 0;
	for (int i = 0; i < 3; i++)
	    {
		capacitate = capacitate + greutate[i].capacitate();
	    }

	return capacitate;
    }
}

class ColectieGreutati extends Greutate
{
    private int maxGreutati = 0;
    private Greutate greutate[];
    private int index = 0;
    
    public ColectieGreutati(int val)
    {
	maxGreutati = val;
	greutate = new Greutate[maxGreutati];
    }

    public void adauga(Greutate g)
    {
	if (index >= maxGreutati)
	    return;

	greutate[index] = g;
	index++;
    }

    public int capacitate()
    {
	int capacitate = 0;
	for (int i = 0; i < index; i++)
	    {
		capacitate = capacitate + greutate[i].capacitate();
	    }

	return capacitate;
    }


    public double medie()
    {
	if (index == 0) return 0;
	return capacitate()/(double)index;
    }
}
