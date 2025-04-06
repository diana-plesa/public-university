class Main
{
    public static void main(String args[])
    {
	Tir t1 = new Tir();
	t1.adaugaRemorca(10, "1");
	t1.adaugaRemorca(15, "2");
	System.out.println(t1.getIndex());
	//System.out.println(t1.toString());
	
    }
}

class Tir
{
    private Remorca remorca[] = new Remorca[5];
    private int index = 0;
    private int totalCantitate = getTotalCantitate();

    public int getIndex()
    {
	return index;
    }

    public boolean adaugaRemorca(int cantitate, String inmatriculare)
    {
	if (index >= 5)	return false;
	    
	remorca[index] = new Remorca(cantitate, inmatriculare);
	index++;
	return true;
    }

    public boolean adaugaRemorca(Remorca remorcaNoua)
    {
	if (index >= 5)	return false;
	    
	remorca[index] = remorcaNoua;
	index++;
	return true;
    }

    public Remorca stergeRemorca(String inmatriculare)
    {
	Remorca remorcaStearsa = null;
	for (int i = 0; i < index; i++)
	    {
	        if (remorca[i].getNrInmatriculare() == inmatriculare)
		    {
			remorcaStearsa = remorca[i];

			for (int j = i; j < index; j++)
			    {
				remorca[j] = remorca[j + 1];
			    }
		    }
	    }

	return remorcaStearsa;
    }

    public int getTotalCantitate()
    {
	int total = 0;
	for (int i = 0; i < index; i++)
	    {
		total = total + remorca[i].getCantitate();
	    }
	return total;

    }

    public boolean equals(Object o)
    {
	if (o instanceof Tir)
	    {
		return ((Tir)o).totalCantitate == totalCantitate;
	    }
	else
	    {
		return false;
	    }
	    
    }

    public String toString()
    {
	String str = "Tir -> ";
	for (int i = 0; i < index; i++)
	    {
		str = str + "R[" + i + "]" + remorca[i].toString() + "-> ";
	    }

	return str;
    }


}

class Remorca
{
    private int cantitate;
    private String nrInmatriculare;
    private static int nrCutii = 0;
    private static int nrRemorci = 0;

    public Remorca(int cantitate, String date)
    {
	this.cantitate = cantitate;
	nrInmatriculare = date;
	nrRemorci++;
    }

    public Remorca(String date)
    {
	if (nrRemorci != 0)
	    cantitate = nrCutii + 1;
	else
	    cantitate = 10;
    }

    public String getNrInmatriculare()
    {
	return nrInmatriculare;
    }

    public int getCantitate()
    {
	return cantitate;
    }

    public String toString()
    {
	return ("(" + nrInmatriculare + ", " + cantitate +")");
    }
}
