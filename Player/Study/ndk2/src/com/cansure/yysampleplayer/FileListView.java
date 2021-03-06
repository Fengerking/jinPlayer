/*******************************************************************************
	File:		file list view.java

	Contains:	the file list UI implement file.

	Written by:	Fenger King

	Change History (most recent first):
	2014-01-05		Fenger			Create file

*******************************************************************************/
package com.cansure.yysampleplayer;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Intent;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.ImageView;
import android.widget.SimpleAdapter;
import android.widget.SimpleAdapter.ViewBinder;

import android.view.WindowManager;
import android.view.Display;
import android.graphics.Point;
import android.graphics.Bitmap;
import java.nio.ByteBuffer;


import com.cansure.mediaEngine.*;

public class FileListView extends Activity {
	private static int	m_nThumbWidth = 96;
	private static int	m_nThumbHeight = 64;
	
	private String							m_strRootPath = null;
	private String							m_strListPath = null;
	private ListView						m_lstFiles = null;
	private AdapterView.OnItemClickListener m_lvListener = null;
	
	private MediaPlayer						m_Player = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {			
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_list_view);
        
        initListView ();
    	
		m_Player = new MediaPlayer();

		String apkPath = "/data/data/" + this.getPackageName() + "/lib/";
		m_Player.Init(this, apkPath);

        File file = Environment.getExternalStorageDirectory();   
        m_strRootPath = file.getPath();   
        
        updateFileList (m_strRootPath);
    }
    
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) 
		{
	    	if (m_strListPath.equals(m_strRootPath)) {
	    		System.exit(0);
				//finish ();
			}
			else {
				File file = new File (m_strListPath);
				m_strListPath = file.getParent();
				updateFileList (m_strListPath);
			}

			return true;
		}

		return super.onKeyDown(keyCode, event);
	}	
	
	@Override
	protected void onDestroy() {
		if (m_Player != null) {
			m_Player.Stop();
			m_Player.Uninit();
			m_Player = null;
		}	
		super.onDestroy();
	}
    
    private void initListView () {
       	m_lvListener = new AdapterView.OnItemClickListener() {
    		@Override
    		public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
    			SimpleAdapter adapter = (SimpleAdapter)m_lstFiles.getAdapter();
    			Map<String, Object> map = (Map<String, Object>)adapter.getItem(position);		
    			String  strFile = (String) map.get("path");
    			String	strDir = (String) map.get("dir");
    			
    			if (strDir.equals("1")) {
    				updateFileList (strFile);
    			} else {
    				Intent intent = new Intent(FileListView.this, PlayerView.class);				
    				intent.setData(Uri.parse(strFile));																
    				startActivity(intent);				
    			}			
    		}
    	};
    	m_lstFiles = (ListView)findViewById (R.id.listViewFile);   	
        m_lstFiles.setOnItemClickListener(m_lvListener);
    }
	
    private void updateFileList (String strPath){  	
    	m_strListPath = strPath;
    	
    	ArrayList<Map<String, Object>> list = getFileList(strPath); 	
		SimpleAdapter adapter = new SimpleAdapter(this, list, R.layout.list_item,
				new String[]{"name","img"}, new int[]{R.id.name, R.id.img});    
		
		thumbViewBinder thumbView = new thumbViewBinder ();
		adapter.setViewBinder(thumbView);
		
		Comparator comp = new nameComparator();
		Collections.sort(list, comp);
		
		m_lstFiles.setAdapter(adapter);	   	
    }
    
	private ArrayList<Map<String, Object>> getFileList(String strPath) {
		ArrayList<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
		File fPath = new File(strPath);
		File[] fList = fPath.listFiles();
	
		HashMap<String, Object> map;
		if (fList != null) {
			for (int i = 0; i < fList.length; i++) 
			{
				File file = fList[i];
				if (file.isHidden()) 
					continue;

				if (file.isDirectory()) {
					File[] fSub = file.listFiles();
					if (fSub == null)
						continue;
					if (fSub.length  <= 0)
						continue;
				}
				
				map = new HashMap<String, Object>();
				map.put("name", file.getName());
				map.put("path", file.getPath());
				if (file.isDirectory()){
					map.put("img", R.drawable.item_folder);
					map.put("dir", "1");
				}
				else {
/*					
					Bitmap bmpImg = Bitmap.createBitmap(m_nThumbWidth, m_nThumbHeight, Bitmap.Config.ARGB_8888 );			
					int nRC = m_Player.GetThumb(file.getPath(), m_nThumbWidth, m_nThumbHeight, bmpImg);
					if (nRC >= 0)
						map.put("img", bmpImg);
					else
*/					
						map.put("img", R.drawable.item_video);
					map.put("dir", "0");
				}
				list.add(map);
			}
		}		
		return list;
	}    

	public class nameComparator implements Comparator<Object> {
		@SuppressWarnings("unchecked")
		public int compare(Object o1, Object o2) {
			HashMap<String, Object> p1 = (HashMap<String, Object>) o1;
			HashMap<String, Object> p2 = (HashMap<String, Object>) o2;
			String strName1, strName2, strDir1, strDir2;
			strName1 = (String) p1.get("name");
			strName2 = (String) p2.get("name");
			strDir1 = (String) p1.get("dir");
			strDir2 = (String) p2.get("dir");

			if (strDir1.equals("1") && strDir2.equals("0") ){
				return -1;
			} else if (strDir1.equals("0") && strDir2.equals("1") ){
				return 1;
			} else {
				if (strName1.compareToIgnoreCase(strName2) > 0) {
					return 1;
				} else {
					return -1;
				}
			}
		}
	}	
	
	public class thumbViewBinder implements ViewBinder {
		public boolean setViewValue(View view, Object data, String textRepresentation) {
            if((view instanceof ImageView) && (data instanceof Bitmap)) {  
                ImageView imageView = (ImageView) view;  
                Bitmap bmp = (Bitmap) data;  
                imageView.setImageBitmap(bmp);  
                return true;  
            } 
			return false;
		}
	}

}
