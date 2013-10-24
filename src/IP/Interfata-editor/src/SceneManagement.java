
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import net.miginfocom.swing.MigLayout;
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class SceneManagement extends javax.swing.JPanel {

    private List<SceneObject> objects;
    private List<ObjectEditor> editors;
    private String extraData;
    int objectCount;
    
    


    /**
     * Creates new form SceneManagement
     */
    public SceneManagement() {


        initComponents();
        
        objectCount = 0;
        objects = new ArrayList<SceneObject>();
        editors = new ArrayList<ObjectEditor>();
        
        
    }

    public SceneManagement(String FileName){

        initComponents();
        objects = new ArrayList<SceneObject>();
        editors = new ArrayList<ObjectEditor>();
        
        parseSMFile(FileName);

    }
    
    private void addObject(SceneObject obj){
            ObjectEditor a;
           
         objectCount+=1;
         
         objects.add(obj);
         
         a = new ObjectEditor(obj);
         editors.add(a);
         
         this.add(a,"wrap");
         refresh();
        
    }
    private void refresh() {
        this.revalidate();
 }    
  
   private void parseSMFile(String FilePath){
   
       String[] temp,temp2;
       try{
       FileReader fstream = new FileReader(FilePath);
       BufferedReader in = new  BufferedReader(fstream);
       
       String strLine;
       
       strLine = in.readLine();
       strLine = in.readLine();
       
       temp = strLine.split(" ");
       
       int objCount = (int) new Integer(temp[1]);
       
       for(int i=0;i<objCount;i++){
           SceneObject o=new SceneObject(i);
           
           strLine = in.readLine();
           strLine = in.readLine();
           temp = strLine.split(" ");
           o.modelID = (int) new Integer(temp[2]);
           
           strLine = in.readLine();
           temp = strLine.split(" ");
           o.setNr2DTextures((int) new Integer(temp[1]));
           
           for(int j=0;j<o.nr2dTextures;j++){
           
               strLine = in.readLine();
               temp = strLine.split(" ");
               
               o.add2DTexture((int) new Integer(temp[2]), j);
           }
           
           strLine = in.readLine();
           temp = strLine.split(" ");
           o.setNrCubeTextures((int) new Integer(temp[1]));
          
           for(int j=0;j<o.nrCubeTextures;j++){
           
               strLine = in.readLine();
               temp = strLine.split(" ");
               
               o.addCubeTexture((int) new Integer(temp[2]), j);
           }
           strLine = in.readLine();
           temp = strLine.split(" ");
           o.setShaderId((int) new Integer(temp[2]));
      
           strLine = in.readLine();
           temp = strLine.split(" ");
           
           temp2 = temp[1].split(",");
           o.setPosition((int) new Integer(temp2[0]),
                         (int) new Integer(temp2[1]),
                         (int) new Integer(temp2[2]));
           
           strLine = in.readLine();
           temp = strLine.split(" ");
           
           temp2 = temp[1].split(",");
           o.setRotation((int) new Integer(temp2[0]),
                         (int) new Integer(temp2[1]),
                         (int) new Integer(temp2[2]));
           
           strLine = in.readLine();
           temp = strLine.split(" ");
           
           temp2 = temp[1].split(",");
           o.setScale((int) new Integer(temp2[0]),
                         (int) new Integer(temp2[1]),
                         (int) new Integer(temp2[2]));
           
           strLine = in.readLine();
           temp = strLine.split(" ");
           o.setNrOtherData((int) new Integer(temp[1]));
           
           for(int j =0;j<o.nrOtherData;j++){
               strLine = in.readLine();
               o.addOtherData(strLine, j);
           }
           
           addObject(o);
       }
       
       
      // System.out.println("NR : "+temp[1]);
                     
       }catch (Exception e){e.printStackTrace();}
   } 
    
    private void writeSMFile(){
    
        String filePath = new String("C:\\Users\\cristi\\Desktop\\IP\\Editor-scene\\Proiect\\SM.txt");
        
        for(int i =0;i<editors.size();i++)
        {
           editors.get(i).saveValues();
        }
        
        
        try{
        FileWriter fstream = new FileWriter(filePath);
        BufferedWriter out = new BufferedWriter(fstream);
        
        out.write("#OBJECTS\r\n");
        out.write("NROBJECTS "+ objectCount +"\r\n");
        
        for (int i = 0;i<objects.size();i++)
        {
         out.write("ID "+objects.get(i).ID+"\r\n");
         out.write("MODEL ID "+objects.get(i).modelID+"\r\n");
         out.write("NR2DTEXTURES "+objects.get(i).nr2dTextures+"\r\n");
         
         for (int j = 0; j<objects.get(i).nr2dTextures;j++){
             
             out.write("TEXTURE2D ID "+objects.get(i).TwoDTextures[j]+"\r\n");
         }
            
         out.write("NRCUBETEXTURES "+objects.get(i).nrCubeTextures+"\r\n");
         
         for(int j = 0;j<objects.get(i).nrCubeTextures;j++){
             
             out.write("TEXTURECUBE ID "+objects.get(i).cubeTextures[j]+"\r\n");
         }
         
         out.write("SHADER ID "+objects.get(i).shaderId+"\r\n");
         out.write("POS "+objects.get(i).pos.x+","
                         +objects.get(i).pos.y+","
                         +objects.get(i).pos.z+"\r\n");
         
         out.write("ROT "+objects.get(i).rot.x+","
                         +objects.get(i).rot.y+","
                         +objects.get(i).rot.z+"\r\n");
         out.write("SCALE "+objects.get(i).scale.x+","
                         +objects.get(i).scale.y+","
                         +objects.get(i).scale.z+"\r\n");
        
         out.write("NROTHERDATA 0"+"\r\n");
         
         /*         for(int j = 0;j<objects.get(i).nrOtherData;j++){
          * 
          * out.write(objects.get(i).otherData[j]+"\r\n");
          * }*/
        }
        
         out.write(extraData);
        out.close();
        }catch(Exception e){
            e.printStackTrace();
        }
        
        
    }

    private void initComponents(){
    

        jButton1 = new javax.swing.JButton();

        this.setLayout(new MigLayout());
        jButton1.setText("Add Object");
        jButton1.setSize(50, 12);
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        
        this.add(jButton1);
    
                jButton2 = new javax.swing.JButton();

       
        jButton2.setText("Save File");
        jButton2.setSize(50, 12);
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });
        
        this.add(jButton2,"wrap 15");
        

        extraData=new String("#CAMERA\r\n"
                + "FAR 10000\r\n"
                + "NEAR 0.1\r\n"
                + "FOV 1\r\n"
                + "#LIGHTS\r\n"
                + "AMBIENTALA 1.0,1.0,1.0\r\n"
                + "NRLIGHTS 3\r\n"
                + "ID 0\r\n"
                + "COLOR 1.0,0.0,0.0\r\n"
                + "TYPE POINT\r\n"
                + "POSITION 0,0,-200\r\n"
                + "MOVING AXISX\r\n"
                + "RADIUS 800.0\r\n"
                + "SPEED 1000.0\r\n"
                + "ID 1\r\n"
                + "COLOR 0.0,0.0,1.0\r\n"
                + "TYPE POINT\r\n"
                + "POSITION 1.0,0.0,-200.0\r\n"
                + "MOVING CIRCLEX\r\n"
                + "RADIUS 50.0\r\n"
                + "SPEED 10.0\r\n"
                + "ID 2\r\n"
                + "COLOR 1.0,1.0,1.0\r\n"
                + "TYPE DIR\r\n"
                + "DIRECTION 0.0,0.0,-1.0");

    }
    

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        // TODO add your handling code here:
        SceneObject b=new SceneObject(objectCount);

        addObject(b);

    }//GEN-LAST:event_jButton1ActionPerformed

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {                                         

        writeSMFile();

    }                                  
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    // End of variables declaration//GEN-END:variables
    private javax.swing.JButton jButton2;

}
