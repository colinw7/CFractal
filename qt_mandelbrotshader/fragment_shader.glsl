varying vec2      v_Coordinates;

uniform sampler2D u_TextureUnit;
uniform float     u_XMin;
uniform float     u_YMin;
uniform float     u_XMax;
uniform float     u_YMax;
uniform int       u_MaxIter;

void main()                    		
{
  //vec2 c;
  //c.x = v_Coordinates.x*(u_XMax - u_XMin) + u_XMin;
  //c.y = v_Coordinates.y*(u_YMax - u_YMin) + u_YMin;

  //float cx = v_Coordinates.x*u_XMax + (1.0 - v_Coordinates.x)*u_XMin;
  //float cy = v_Coordinates.y*u_YMax + (1.0 - v_Coordinates.y)*u_YMin;

  float cx = (1.0f + v_Coordinates.x)*(u_XMax - u_XMin)/2.0f + u_XMin;
  float cy = (1.0f + v_Coordinates.y)*(u_YMax - u_YMin)/2.0f + u_YMin;

  int i;
  int j = 256;

  float zx = cx;
  float zy = cy;

  for (i = 0; i < 256; i++) {
    float x = (zx*zx - zy*zy) + cx;
    float y = (zy*zx + zx*zy) + cy;

    if (j == 256 && (x*x + y*y) > 4.0) {
      j = i;
      x = 0.0;
      y = 0.0;
    }

    zx = x;
    zy = y;
  }

  if (j == 256) {
    gl_FragColor = vec4(0,0,0,1);
  }
  else {
    vec2 fc;

    fc.x = float(j)/255.0f;
    fc.y = 0.0;

    //fc.y = v_Coordinates.y;

    //fc.x = v_Coordinates.x;
    //fc.y = v_Coordinates.y;

    gl_FragColor = texture2D(u_TextureUnit, fc);

    //float g = float(j)/255.0f;
    //gl_FragColor = vec4(g, g, g, 1);
  }
}
