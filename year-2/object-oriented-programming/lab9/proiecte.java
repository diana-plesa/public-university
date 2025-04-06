

class InvestmentCompany
{
    private Project proiect[] = new Project[10];
    private int nrProiecte = 0;

    public String toString()
    {
	String str = "";
	for (int i = 0; i < nrProiecte; i++)
	    {
	        str = str + "project " + proiect[i].toString() + " has risk " + proiect[i].getRisk() + "\n";
	    }
	return str;
    }
    
    public void addProject(Project p)
    {
	if (nrProiecte == proiect.length)
	    resizeProiect();
	
	proiect[nrProiecte] = p;
	nrProiecte++;
    }

    public void resizeProiect()
    {
	Project proiectNou[] = new Project[proiect.length * 2];

	for (int i = 0; i < proiect.length; i++)
	    proiectNou[i] = proiect[i];

	proiect = proiectNou;
    }

    public Project getBestInvestment()
    {
	if (nrProiecte == 0)
	    return null;
	
	Project bestProject = proiect[0];
	double minRisk = proiect[0].getRisk();
	
	for (int i = 1; i < nrProiecte; i++)
	    {
		if (minRisk > proiect[i].getRisk())
		    {
			minRisk = proiect[i].getRisk();
			bestProject = proiect[i];
		    }
	    }

	return bestProject;
    }

    public static void main(String args[])
    {

       	Member mem1 = new Member(31, "Desmond");
	Member mem2 = new Member(32, "Erika");
	Member mem3 = new Member(28, "Robert");

	Member mem4 = new Member(32, "Olivia");
	Member mem5 = new Member(31, "Mark");
	Member mem6 = new Member(26, "Rosa");
	
	MilitaryProject m1 = new MilitaryProject(mem1, "M1", "baza militara", 2000, "9 noiembrie", "x");
	OpenSourceProject o1 = new OpenSourceProject(mem2, "O1", "security system", 1000, "Partener1 Partener2");
	CommercialProject c1 = new CommercialProject(mem3, "C1", "film", 4000, "25 noiembrie");
	

	c1.addMember(mem4);
	c1.addMember(mem5);
	c1.addMember(mem6);
	c1.setNrEchipe(2);

	o1.addMember(mem5);
	o1.addMember(mem6);

	m1.addMember(mem4);
	m1.addMember(mem5);
	m1.addMember(mem6);

	InvestmentCompany I = new InvestmentCompany();
	I.addProject(m1);
	I.addProject(o1);
	I.addProject(c1);

	Project bestProject = I.getBestInvestment();

	System.out.println(I.toString());

	System.out.println("Best project is " + bestProject.toString() + " with risk " + bestProject.getRisk());
        
    }
}

interface Risky
{
    double getRisk();
}

abstract class Project implements Risky
{
     private Member manager;
     private String titlu;
     private String obiectiv;
     private long fonduri;

     public abstract void addMember(Member m);

     public Project(Member manager, String titlu, String obiectiv, long fonduri)
     {
       	this.manager = manager;
       	this.titlu = titlu;
       	this.obiectiv = obiectiv;
       	this.fonduri = fonduri;
     }

    public String toString()
    {
	return titlu;
    }
    
    public Member getManager()
    {
	return manager;
    }

    public void setManager(Member val)
    {
	manager = val;
    }

    public String getTitlu()
    {
	return titlu;
    }

    public void setTitlu(String val)
    {
	titlu = val;
    }

    public String getObiectiv()
    {
	return obiectiv;
    }

    public void setObiectiv(String val)
    {
	obiectiv = val;
    }

    public long getFonduri()
    {
	return fonduri;
    }

    public void setFonduri(long val)
    {
	fonduri = val;
    }
}

class CommercialProject extends Project
{
    private String deadline;
    private Member[] membru = new Member[15];
    private long fonduriMarketing = getFonduri()/2;
    private int nrEchipe;
    private int nrMembri = 0;

    public CommercialProject(Member manager, String titlu, String obiectiv, long fonduri, String deadline)
    {
	super(manager, titlu, obiectiv, fonduri);
	this.deadline = deadline;
    }

    public void setNrEchipe(int nr)
    {
	nrEchipe = nr;

	if (nrEchipe >= nrMembri)
	    nrEchipe = 0;
    }

    public void addMember(Member m)
    {
	if (nrMembri >= 15)
	    return;

	membru[nrMembri] = m;
	nrMembri++;
    }

    public double getRisk()
    {
	return ((double)nrEchipe) * (double)3.0 / ((double)nrMembri) / ((double)getFonduri()) - ((double)fonduriMarketing);
    }
}

class OpenSourceProject extends Project
{
    private String mailingList;
    private Member[] membru = new Member[10];
    private int nrMembri = 0;

    public OpenSourceProject(Member manager, String titlu, String obiectiv, long fonduri, String mailingList)
    {
        super(manager, titlu, obiectiv, fonduri);
	this.mailingList = mailingList;
    }

    public void addMember(Member m)
    {
	if (nrMembri > membru.length)
	    resizeMembri();
	
	membru[nrMembri] = m;
       	nrMembri++;
    }

    public void resizeMembri()
    {
	Member membruNou[] = new Member[membru.length * 2];

	for (int i = 0; i < membru.length; i++)
	    membruNou[i] = membru[i];

	membru = membruNou;
    }

    public double getRisk()
    {
       	return (double)nrMembri / (double)getFonduri();
    }
}

class MilitaryProject extends Project
{
    private String deadline;
    private int nrMembri = 0;
    private Member[] membru = new Member[15];
    private String parola;

    public MilitaryProject(Member manager, String titlu, String obiectiv, long fonduri, String deadline, String parola)
    {
	super(manager, titlu, obiectiv, fonduri);
       	/*setManager(manager);
       	setTitlu(titlu);
       	setObiectiv(obiectiv);
       	setFonduri(fonduri);*/
       	this.deadline = deadline;
       	this.parola = parola;
    }

    public void addMember(Member m)
    {
       	if (nrMembri >= 15)
       		return;

       	membru[nrMembri] = m;
       	nrMembri++;
    }

    public double getRisk()
    {
	
	return (double)nrMembri / (double)parola.length() / (double)getFonduri();
    }
}

class Member
{
    private int varsta;
    private String nume;

    public Member(int varsta, String nume)
    {
       	this.varsta = varsta;
       	this.nume = nume;
    }
}
