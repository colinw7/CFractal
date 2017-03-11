attribute vec4 a_Position;
attribute vec2 a_Coordinates;
varying vec2   v_Coordinates;

void main()
{
  v_Coordinates = a_Coordinates;
  gl_Position   = vec4(a_Coordinates.x, a_Coordinates.y, 1.0f, 1.0f);
}
