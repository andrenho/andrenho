package com.colonialtrader;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class ColonialTrader extends ListActivity {
	
	private static final String[] items = { "teste1", "Teste 2", "TESTE 3" };
	
	class CityAdapter extends ArrayAdapter<String> 
	{
		
		public CityAdapter() 
		{
			super(ColonialTrader.this, R.layout.city_row, R.id.cityname, items);
		}
		
		@Override
		public View getView(int position, View convertView, ViewGroup parent) 
		{
			View row = super.getView(position, convertView, parent);
			TextView tv = (TextView)row.findViewById(R.id.cityinfo);
			tv.setText("Teste");
			return row;
		}
		
	}
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setListAdapter(new CityAdapter());
    }
}