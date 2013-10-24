/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class TextureResourceCube {
    
        int ID;
    String filePath;
    String wrappingMode;
    
    public TextureResourceCube(int id, String path,String path2) {
        
        ID = id ;
        filePath = new String(path);
        wrappingMode = new String(path2);
    }
    
    
    public TextureResourceCube(int id) {
        
        ID = id ;
        filePath = new String();
        wrappingMode = new String();
    }
    
    public void setFilePath(String path ){
    
        filePath = path;
    }
    
    public void setWrappingMode(String path){
    
        wrappingMode = path;
    }
    
    
}
