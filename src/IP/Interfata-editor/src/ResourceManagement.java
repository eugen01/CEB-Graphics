import java.awt.Dimension;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JButton;
import javax.swing.JScrollPane;
import net.miginfocom.swing.MigLayout;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
public class ResourceManagement extends javax.swing.JPanel {


    
    private List<ModelResource> models;
    private List<TextureResource2D> textures2D;
    private List<TextureResourceCube> texturesCube;
    private List<ShaderResource> shaders;
    
    
    private List <ModelChooser> modelEditors;
    private List <TextureEditor> texture2DEditors;
    private List <TextureEditor> textureCubeEditors;
    private List <ShaderEditor> shaderEditors;
    
    int modelCount,texture2DCount,textureCubeCount,shaderCount;
    int objectCount;
    private JButton jButton2,jButton3,jButton4,jButton5,jButton1;
    
    
    
    JScrollPane modelSP;

    
    /**
     * Creates new form SceneManagement
     */
    public ResourceManagement() {


        initComponents();
        
        objectCount = 0;


        models = new ArrayList<ModelResource>();
        textures2D = new ArrayList<TextureResource2D>();
        texturesCube = new ArrayList<TextureResourceCube>();
        shaders = new ArrayList<ShaderResource>();
        
        
        modelEditors = new ArrayList<ModelChooser>();
        modelCount = 0;

        texture2DEditors = new ArrayList<TextureEditor>();
        texture2DCount = 0;
       
        textureCubeEditors = new ArrayList<TextureEditor>();
        textureCubeCount = 0;
        
        shaderEditors = new ArrayList<ShaderEditor>();
        shaderCount = 0;
        
        
    }

    public ResourceManagement(String FileName){

        initComponents();

        models = new ArrayList<ModelResource>();
        textures2D = new ArrayList<TextureResource2D>();
        texturesCube = new ArrayList<TextureResourceCube>();
        shaders = new ArrayList<ShaderResource>();
        
        
        modelEditors = new ArrayList<ModelChooser>();
        modelCount = 0;

        texture2DEditors = new ArrayList<TextureEditor>();
        texture2DCount = 0;
       
        textureCubeEditors = new ArrayList<TextureEditor>();
        textureCubeCount = 0;
        
        shaderEditors = new ArrayList<ShaderEditor>();
        shaderCount = 0;
        
        parseRMFile(FileName);
    }
    
   
    private void addModel(ModelResource obj){
        
        ModelChooser mc;
        
        modelCount+=1;
        models.add(obj);
        
        mc = new ModelChooser(obj);
        
        modelEditors.add(mc);
        
        this.add(mc,"wrap");
        refresh();
        
    }
    
    private void addTexture2D(TextureResource2D obj){
        TextureEditor te;
        
        texture2DCount+=1;    
        textures2D.add(obj);
        te = new TextureEditor(obj);
        texture2DEditors.add(te);
        
        this.add(te,"wrap");
        refresh();
        
    }
    
    private void addTextureCube(TextureResourceCube obj){
        
        TextureEditor te;
        
        textureCubeCount+=1;    
        texturesCube.add(obj);
        te = new TextureEditor(obj);
        texture2DEditors.add(te);
        
        this.add(te,"wrap");
        refresh();
    }    
    
    private void addShader(ShaderResource obj){
    
        ShaderEditor se;
        shaderCount+=1;
        shaders.add(obj);
        se = new ShaderEditor(obj);
        
        shaderEditors.add(se);
        
        this.add(se,"wrap");
        refresh();
    }
    

    private void refresh() {
        this.revalidate();
 }    
    
    private void parseRMFile(String filePath){
    
        String[] temp;
        try{
            FileReader fstream = new FileReader(filePath);
            BufferedReader in = new  BufferedReader(fstream);
        
            String strLine;
            strLine = in.readLine();//#MODELS
            strLine = in.readLine();//NRMODELS X
        
            temp = strLine.split(" ");
            int count = (int) new Integer(temp[1]);
            
            for(int i=0;i<count;i++){
                ModelResource mr = new ModelResource(i);
                
                strLine = in.readLine();//ID
                
                strLine = in.readLine();
                temp = strLine.split(" ");
                mr.setFilePath(temp[1]);
                
                addModel(mr);
            }
            strLine = in.readLine();//_
            strLine = in.readLine();//#2DTEXTURES
            strLine = in.readLine();//NR2DTEXTURES X
            
            temp = strLine.split(" ");
            count = (int) new Integer(temp[1]);
            for(int i=0;i<count;i++){
                TextureResource2D tr2 = new TextureResource2D(i);
                strLine = in.readLine();
                strLine = in.readLine();
                temp = strLine.split(" ");
                tr2.setFilePath(temp[1]);
                strLine = in.readLine();
                temp = strLine.split(" ");
                tr2.setWrappingMode(temp[1]);
                
                addTexture2D(tr2);
            }
            
            strLine = in.readLine();//#CUBETEXTURES
            strLine = in.readLine();//NRCUBETEXTURES X
            
            temp = strLine.split(" ");
            count = (int) new Integer(temp[1]);
            for(int i=0;i<count;i++){
                TextureResourceCube trc = new TextureResourceCube(i);
                strLine = in.readLine();
                strLine = in.readLine();
                temp = strLine.split(" ");
                trc.setFilePath(temp[1]);
                strLine = in.readLine();
                temp = strLine.split(" ");
                trc.setWrappingMode(temp[1]);
                
                addTextureCube(trc);
            }
            
            strLine = in.readLine();//_
            strLine = in.readLine();//#SHADERS
            strLine = in.readLine();//NRSHADERS X
            
            temp = strLine.split(" ");
            count = (int) new Integer(temp[1]);
            
            for(int i=0;i<count;i++){
                ShaderResource sr = new ShaderResource(i);
                strLine = in.readLine();
                strLine = in.readLine();
                temp = strLine.split(" ");
                sr.setVsFilePath(temp[1]);
                strLine = in.readLine();
                temp = strLine.split(" ");
                sr.setFsFilePath(temp[1]);
                strLine = in.readLine();
                
                addShader(sr);
            }
           in.close();
        }catch(Exception e){e.printStackTrace();}
        
    }
    
    private void writeRMFile(){
    
        String filePath = new String("C:\\Users\\cristi\\Desktop\\IP\\Editor-scene\\Proiect\\RM.txt");
        
        for (int i=0;i<modelEditors.size();i++){
                modelEditors.get(i).saveValues();
        }
        for (int i=0;i<texture2DEditors.size();i++){
                texture2DEditors.get(i).saveValues();
        }
        for (int i=0;i<textureCubeEditors.size();i++){
                textureCubeEditors.get(i).saveValues();
        }
        for (int i=0;i<shaderEditors.size();i++){
                shaderEditors.get(i).saveValues();
        }
        
        try{
            FileWriter fstream = new FileWriter(filePath);
            BufferedWriter out = new BufferedWriter(fstream);
            
            out.write("#MODELS\r\n");
            out.write("NRMODELS "+models.size()+"\r\n");
            
            for (int i=0;i<models.size();i++){
                out.write("ID "+models.get(i).ID+"\r\n");
                out.write("FILE "+models.get(i).filePath+"\r\n");
            }
            
            out.write("\r\n");
            out.write("#2DTEXTURES\r\n");
            out.write("NR2DTEXTURES "+textures2D.size()+"\r\n");
            
            for (int i=0;i<textures2D.size();i++){
                out.write("ID "+textures2D.get(i).ID+"\r\n");
                out.write("FILE "+textures2D.get(i).filePath+"\r\n");
                out.write("WRAPPINGMODE "+textures2D.get(i).wrappingMode+"\r\n");
            }
            
            out.write("#CUBETEXTURES\r\n");
            out.write("NRCUBETEXTURES "+texturesCube.size()+"\r\n");
            
            for (int i=0;i<texturesCube.size();i++){
                out.write("ID "+texturesCube.get(i).ID+"\r\n");
                out.write("FILE "+texturesCube.get(i).filePath+"\r\n");
                out.write("WRAPPINGMODE "+texturesCube.get(i).wrappingMode+"\r\n");
              
            }
            
            out.write("\r\n");
            out.write("#SHADERS\r\n");
            out.write("NRSHADERS "+shaders.size()+"\r\n");
            
            for (int i=0;i<shaders.size();i++){
                out.write("ID "+shaders.get(i).ID+"\r\n");
                out.write("FILE "+shaders.get(i).vsFilePath+"\r\n");
                out.write("FILE "+shaders.get(i).fsFilePath+"\r\n");
                if(i==shaders.size()-1){
                    out.write("NRSTATES 0");
                }else{
                    out.write("NRSTATES 0\r\n");
                }
            }
            
            out.close();
        }catch(Exception e){e.printStackTrace();}
        
       
    }

    private void initComponents(){
    

        jButton1 = new javax.swing.JButton();

        this.setLayout(new MigLayout());
        jButton1.setText("Save File");
        jButton1.setSize(50, 12);
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        
        this.add(jButton1,"wrap 5");
    
        
        jButton2 = new javax.swing.JButton();
        jButton2.setText("Add model");
        jButton2.setSize(50, 12);
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });
        
        
        this.add(jButton2,"wrap 5");
    
        
        jButton3 = new javax.swing.JButton();
        jButton3.setText("Add 2D Texture");
        jButton3.setSize(50, 12);
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });
        
        this.add(jButton3);
        
                jButton4 = new javax.swing.JButton();

        this.setLayout(new MigLayout());
        jButton4.setText("Add Cube Texture");
        jButton4.setSize(50, 12);
        jButton4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton4ActionPerformed(evt);
            }
        });
        
        this.add(jButton4,"wrap 5");
    
        
        jButton5 = new javax.swing.JButton();
        jButton5.setText("Add shader");
        jButton5.setSize(50, 12);
        jButton5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton5ActionPerformed(evt);
            }
        });
        
        this.add(jButton5,"wrap 5");


    }
    
    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {                                         
        // TODO add your handling code here:
        writeRMFile();
    }                                        

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {                                         

        ModelResource b=new ModelResource(modelCount);

        addModel(b);

    }    
     private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {                                         
        // TODO add your handling code here:
        TextureResource2D b=new TextureResource2D(texture2DCount);

        addTexture2D(b);
         
    }                                        

      private void jButton4ActionPerformed(java.awt.event.ActionEvent evt) {                                         
        // TODO add your handling code here:
        TextureResourceCube b=new TextureResourceCube(textureCubeCount);

        addTextureCube(b);
         
    }                                        

       private void jButton5ActionPerformed(java.awt.event.ActionEvent evt) {                                         
        // TODO add your handling code here:
        ShaderResource b=new ShaderResource(shaderCount);

        addShader(b);
         

    }                                        

    

}