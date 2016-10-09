查找重复资源  基于Java


import java.io.File;
import java.sql.Ref;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

public class main 
{
	public static int nCount = 0;
	
	//用来存放所有的图片
	public static Map<String, Integer> m_mapData = new HashMap<String, Integer>();
	//用来存放重复图片的路径
	public static Map<String, String> m_mapFilePath = new HashMap<String, String>();
	
	 private static ArrayList<String> filelist = new ArrayList<String>();
	 
	 public static void main(String[] args) throws Exception {
	    
	    String filePath = "/Users/zctech_1/Desktop/CocosEnvironment/Resources/resources-cn";
	    getFiles(filePath);
	    System.out.println("图片共有： " + nCount);
	    int count = 0;
	    for(Map.Entry<String, Integer> entry : m_mapData.entrySet())
	    {
	    	if (entry.getValue() > 1)
	    	{
	    		if (!entry.getKey().contains(".png") && !entry.getKey().contains(".jpg"))
	    			continue;
	    		System.out.println(entry.getKey() + " ---> " + entry.getValue());
	    		count++;
	    		System.out.println("*****************************");
	    		
	    		for(int i = 0; i < filelist.size(); ++i)
	    		{
	    			if (filelist.get(i).contains("/"+entry.getKey()))
	    			{
	    				System.out.println(filelist.get(i));
	    			}
	    		}
	    		System.out.println("*****************************");
	    		System.out.println();
	    		System.out.println();
	    	}
	    }

	    System.out.println("extra png" + count);
	 } 

	 /*
	  * 通过递归得到某一路径下所有的目录及其文件
	  */
	 static void getFiles(String filePath)
	 {
//		 int nCount = 0;
		 File root = new File(filePath);
		 File[] files = root.listFiles();
		 for(File file:files)
		 {     
			 if (m_mapData.containsKey(file.getName()))
			 {
				 m_mapData.put(file.getName(), 2);
			 }
			 else {
				 m_mapData.put(file.getName(), 1);
			}
			 
			 if(file.isDirectory())
			 {//递归调用
			      getFiles(file.getAbsolutePath());
			      
			      
//			      System.out.println("显示"+filePath+"下所有子目录及其文件"+file.getAbsolutePath());
		     }
			 else
		     {
				 filelist.add(file.getAbsolutePath());
				 ++nCount;
//				 System.out.println("显示"+filePath+"下所有子目录"+file.getAbsolutePath());
//				 System.out.println("图片名称为： " + file.getAbsolutePath().lastIndexOf(filePath));
		     } 
			 
	    }
	 }
}