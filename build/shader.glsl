#ifdef VERTEX						 
uniform mat4 u_Projection;				 
uniform mat4 u_Model;						 
uniform mat4 u_View;						 
											 
attribute vec3 a_Position;				     
attribute vec3 a_Normal;				     
attribute vec2 a_TexCoord;					 
											 
varying vec2 v_TexCoord;					 
											 
void main()								 
{											 
 gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1);		 
 v_TexCoord = a_TexCoord;   
 if (a_Normal.x == 43) gl_Position.x = 6;   
}											 
											 
#endif
						 
#ifdef FRAGMENT						 
varying vec2 v_TexCoord;					 
uniform sampler2D u_Texture;

										 
void main()								 
{						
 vec4 tex = texture2D(u_Texture, v_TexCoord);
 gl_FragColor = tex;

}										     
											 
#endif