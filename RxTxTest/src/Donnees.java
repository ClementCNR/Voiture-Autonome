
public class Donnees 
{
	
	SerialTest st = new SerialTest();
	
	private float dist = 0;
	
	
	public float vitesseMoyenne() 
	{
		int type = st.getType();
		float val1 = st.getValeur1();
		float val2 = st.getValeur2();
		
		float vMoy = 0;
		int nbSerie = 0;
		
		if (type == 0)
		{
			nbSerie++;
			vMoy = (vMoy + val1 ) / nbSerie;
		}

		return vMoy;
	}

	public float distParcourue() 
	{
		int type = st.getType();
		float val1 = st.getValeur1();
		float val2 = st.getValeur2();
		
				
		if(type == 0)
		{
			dist = dist + val2;
		}
		
		return dist;
	}
	
	
}
