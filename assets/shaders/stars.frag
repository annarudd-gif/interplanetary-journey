#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;

/*пікселі по горизонталі та вертикалі*/
uniform vec2 u_resolution;
/*швидкість руху зірок*/
uniform vec2 offset;
/*метод який генерує випадкове число*/
float random(vec2 p){
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);}

/*метод який генерує випадкові два числа*/
vec2 random2(vec2 p){
return vec2(random(p),random(p+vec2(5.34573,2.4845)));}

/*метод який генерує зірки*/
vec3 Stars(vec2 uv, float n,float sdvig, float sizeMin, float sizeMax, float YN,
    float minB, float maxB,float speed){ 
    vec2 layerUV=uv;
    layerUV.x+=sdvig;
    layerUV.x+=offset.x*speed;
    vec2 gridUV= layerUV*n;
    vec2 local=fract(gridUV)-0.5;
    vec2 cell= floor(gridUV);
    vec3 summ=vec3(0.0,0.0,0.0);
    float hasStar;
    float starChance;
    vec3 starColor;
    float brightness;
    float core;
    float glow;
    float twinkle;
    vec2 cellOfset;
    vec2 neighborCell;

    

    for(float y=-1.0; y<=1.0;y+=1.0){
        for(float x=-1.0; x<=1.0;x+=1.0){
            cellOfset=vec2(x,y);
            neighborCell=cell+cellOfset;
           

            vec2 starPos=(random2(neighborCell+vec2(4.3457,0.45)))-0.5;
             vec2 shiftedStarPos=cellOfset+starPos;
            float d=length(local-shiftedStarPos);
    
            float a=sizeMax-sizeMin;
            float size= random(neighborCell+vec2(4.5473,6.437))*a+sizeMin;
    
            starChance=random(neighborCell+vec2(2.3646,4.573));
            hasStar=step(YN,starChance);
    
            float s=maxB-minB;
            brightness= random(neighborCell+vec2(2.4575,9.574))*s+minB;
    
            float r= random(neighborCell+vec2(2.4575,7.3457))*0.2-0.1;
            float g= random(neighborCell+vec2(6.43576,3.45345))*0.2-0.1;
            float b= random(neighborCell+vec2(5.435,7.3535345))*0.2-0.1;
            starColor=vec3(1.0+r,1.0+g,1.0+b);
    
            float twinklePhase=random(neighborCell+vec2(5.35768,7.356845))*0.7+0.3;
            float twinkleSpeed=mix(0.5,2.0,random(neighborCell+vec2(5.43575,9.3564)));
            twinkle=(sin(u_time*twinkleSpeed+twinklePhase)*0.5+0.5)*0.4+0.6;
    
            core= smoothstep(size,size*0.3,d);
            glow= size*0.1/max(d,0.001);
            summ+=hasStar*starColor*brightness*(core+glow)*twinkle;}
    }
    
    return summ;
    
    }
/*головний метод*/
void main(){
    /*координати від -0.5 до 0.5, центр у точці 0.0*/
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv-=0.5;
    uv.x*=u_resolution.x/u_resolution.y;
   
   /*градієнтний фон*/
    vec3 bg=mix(vec3(0.0,0.0,0.2),vec3(0.0,0.0,0.0),(uv.y+0.5));

     vec3 color1= Stars(uv,30.0,0.2, 0.03, 0.1,0.67,0.2, 0.4,0.001);
    vec3 color2= Stars(uv,25.0,0.6, 0.07, 0.13,0.95,0.4, 0.8,0.002);
    vec3 color3= Stars(uv,10.0,0.0, 0.06, 0.09,0.995,0.6, 1.0,0.003);
    vec3 color=bg+color1+color2+color3;
    


    gl_FragColor = vec4(color, 1.0);
}











 
    


  
   
 
    
    
    
   
    


   
    