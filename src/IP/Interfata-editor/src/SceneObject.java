/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class SceneObject {

    int ID;
    int nr2dTextures;
    int nrCubeTextures;
    int shaderId;
    int modelID;
    Vector3D pos,rot,scale;
    int nrOtherData;
    int[] cubeTextures;
    int[] TwoDTextures;
    String[] otherData;
    
    int CTindex;
    int TDindex;
    
    private void initDefault(){
        CTindex =0;
        TDindex =0;
        nr2dTextures =0 ;
        nrCubeTextures = 0;
        shaderId = 0;
        modelID = 0;

    }
    
    public SceneObject( int id){
        this.ID = id;
        
        initDefault();
        pos = new Vector3D(0,0,0);
        rot = new Vector3D(0,0,0);
        scale = new Vector3D(0,0,0);
    }
    

    
    public void setNr2DTextures(int val){
            TwoDTextures = new int[val];
            nr2dTextures = val;
    }
    
    public void setNrCubeTextures(int val){
            cubeTextures = new int[val];
            nrCubeTextures = val;
    }
    
    public void setNrOtherData(int val){
        nrOtherData=val;    
        otherData = new String[val];
    }
    public void addOtherData(String line,int pos){
        otherData[pos] = line;
    }
    
    public void add2DTexture(int val , int pos){
            TwoDTextures[pos] = val;
    }
    
    public void addCubeTexture(int val ,int pos){
            cubeTextures[pos] = val;
    }
    
    public void setShaderId(int val){
            shaderId = val;
    }
    
    public void setPosition (int x , int y , int z){
    
            pos.x = x;
            pos.y = y;
            pos.z = z;
    } 
    
    public void setRotation (int x , int y , int z){
    
            rot.x = x;
            rot.y = y;
            rot.z = z;
    } 
        
    public void setScale (int x , int y , int z){
    
            scale.x = x;
            scale.y = y;
            scale.z = z;
    } 
    
    public void setModelId(int id){
    
           modelID = id;
    }
    
    
}


