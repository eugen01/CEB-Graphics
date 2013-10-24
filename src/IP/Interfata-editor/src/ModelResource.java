/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class ModelResource {
       
        int ID;
    String filePath;

    
    public ModelResource(int id, String path) {
        
        ID = id ;
        filePath = new String(path);

    }
    
    
    public ModelResource(int id) {
        
        ID = id ;
        filePath = new String();

    }
    
    public void setFilePath(String path ){
    
        filePath = path;
    }
    
    
    
}
