
import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.io.File;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JScrollPane;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Eugen
 */
class InitialFrame extends JFrame{

      JButton jButton1, jButton2,jButton3;  
    
      public InitialFrame(String name){
        
        
        jButton1 = new JButton("Create New Files");
        jButton2 = new JButton("Use Existing Files");

        jButton3 = new JButton("Start  Application");
        this.setName(name);
        jButton1.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButton2.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButton3.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });   
      
      }


    public void display(){
    
            Toolkit tk = Toolkit.getDefaultToolkit();
        this.getContentPane().setLayout(new BoxLayout(this.getContentPane()
                                            , BoxLayout.Y_AXIS));
        this.getContentPane().add(Box.createVerticalStrut(50));
        this.getContentPane().add(jButton1);
        this.getContentPane().add(Box.createVerticalStrut(50));
        this.getContentPane().add(jButton2);
        this.getContentPane().add(Box.createVerticalStrut(50));
        this.getContentPane().add(jButton3);

        
        this.pack();
       this.setVisible(true);
       this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(300,350);
        this.setLocation((int) tk.getScreenSize().getWidth()/2,
                              (int) tk.getScreenSize().getHeight()/2);
        
    }
  
    private void startEditor(SceneManagement SM , ResourceManagement RM){
        Toolkit tk = Toolkit.getDefaultToolkit();
        JFrame frame = new JFrame("Scene Editor  - GUI File Editor");
        
        
        frame.setSize((int) tk.getScreenSize().getWidth()
                    ,(int) tk.getScreenSize().getHeight());
        
        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setLayout(new BorderLayout());

        JScrollPane scrollPane1;
        scrollPane1 = new JScrollPane(SM,JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED
                                    ,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
       
        scrollPane1.setPreferredSize(new Dimension((int) tk.getScreenSize().getWidth()/2
                    ,(int) tk.getScreenSize().getHeight()));

        frame.getContentPane().add(scrollPane1,BorderLayout.LINE_START);
        
        JScrollPane scrollPane2;
        scrollPane2 = new JScrollPane(RM,JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED
                                    ,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        
        scrollPane2.setPreferredSize(new Dimension((int) tk.getScreenSize().getWidth()/2
                    ,(int) tk.getScreenSize().getHeight()));

        frame.getContentPane().add(scrollPane2,BorderLayout.LINE_END);
        frame.pack();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
    }
    
    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {
    
        SceneManagement s = new SceneManagement();
        ResourceManagement r =new ResourceManagement();
        
        startEditor(s, r);

    
    }
    
    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) { 
    
        JFileChooser fc;
        SceneManagement s ;
        ResourceManagement r; 
        File file;
        
        fc = new JFileChooser();
        fc.setDialogTitle("Open  SM  file");
        
        int returnVal = fc.showOpenDialog(this);
        
        if(returnVal ==JFileChooser.APPROVE_OPTION)
        {
         file = fc.getSelectedFile();
         s= new SceneManagement(file.getAbsolutePath());
         
         fc.setDialogTitle("Open  RM  file");
         
         returnVal = fc.showOpenDialog(this);
         
            if(returnVal ==JFileChooser.APPROVE_OPTION){
                file = fc.getSelectedFile();
                r=new ResourceManagement(file.getAbsolutePath());
            
                startEditor(s,r);
            }
        }
        
        
        
    }
    private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {
    
     try{
         
         
        
         
         Runtime rt = Runtime.getRuntime();
           Process p = rt.exec("NewTrainingFramework.exe");
         int exitStatus = p.waitFor();
           
           System.out.println("Getting Here");
     }catch(Exception e){e.printStackTrace();} 

    
    }
}


public class EditingInterface {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Toolkit tk = Toolkit.getDefaultToolkit();
        
        InitialFrame initFrame = new InitialFrame("Scene Editor  - Option Selection");
        
        initFrame.display();
        
        
        
    }
}
