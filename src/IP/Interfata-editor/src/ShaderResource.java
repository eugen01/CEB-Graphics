/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class ShaderResource {

    int ID;
    String vsFilePath;
    String fsFilePath;
    
    ShaderResource (int id){
     
        this.ID = id;
        vsFilePath = new String();
        fsFilePath = new String();
        
    }
    
    public void setVsFilePath(String path){
    
        vsFilePath = path;
    }
    
    public void setFsFilePath(String path){
    
        fsFilePath = new String(path);
    }
    

}
