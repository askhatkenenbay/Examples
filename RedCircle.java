package RedCircleGame;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
public class RedCircle extends JFrame implements MouseMotionListener, MouseListener{
	private int xPos;
	private int yPos;
	private int width;
	private int height;
	private boolean mouseDown;
	
	public RedCircle(int widthIn, int heightIn) {
		setTitle("Red Circle Game");
		addMouseMotionListener(this);
		addMouseListener(this);
		width=widthIn;
		height = heightIn;
		getContentPane().setBackground(Color.yellow);
		xPos=width/2-20;
		yPos=height/2-20;
		setSize(width,height);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(width,height);
		setLocation(300,300);
		setVisible(true);
	}
	
	//the paint method
	public void paint(Graphics g) {
		super.paint(g);
		g.drawString("Click on the red circle", width/2-60, 50);
		g.setColor(Color.red);
		g.fillOval(xPos, yPos, 20, 20);
		
		if(mouseDown) {
			g.drawString("Keep Trying",width/2-40,height-10);
		}
	}
	
	public void mouseMoved(MouseEvent e) {
		xPos=e.getX()-50;
		yPos=e.getY()-50;
		repaint();
	}
	public void mouseDragged(MouseEvent e) {
		xPos=e.getX()-50;
		yPos=e.getY()-50;
		repaint();
	}
	
	public void mousePressed(MouseEvent e) {
		mouseDown=true;
		repaint();
	}
	
	public void mouseReleased(MouseEvent e) {
		mouseDown=false;
		repaint();
	}
	
	public void mouseClicked(MouseEvent e) {
	}
	
	public void mouseEntered(MouseEvent e) {
	}
	
	public void mouseExited(MouseEvent e) {
	}
}
