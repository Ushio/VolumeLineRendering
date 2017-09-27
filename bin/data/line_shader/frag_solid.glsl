#version 410

layout (location = 0) out vec4 FragColor;

// layout (depth_less) out float gl_FragDepth;

in block
{
  flat vec3 p1;
	flat vec3 color1;
	flat vec3 p2;
	flat vec3 color2;

	smooth float radius;

	smooth vec3 fragViewPos;

	flat vec3 ba;
	flat float dot_ba_ba_inverse;
} In;

uniform mat4 u_pmat;

// sp.xyz: sphere position
// sp.w: sphere radius
bool intSphere(vec4 sp, vec3 ro, vec3 rd, float tm, out float t )
{
    bool  r = false;
    vec3  d = ro - sp.xyz;
    float b = dot(rd,d);
    float c = dot(d,d) - sp.w*sp.w;
    t = b*b-c;
    if( t > 0.0 )
    {
        t = -b-sqrt(t);
        r = (t > 0.0) && (t < tm);
    }

    return r;
}

#define OPTIM_BRUTE_FORCE 1

// 線分S(t)=sa+t(sb-sa), 0<=t<=1の、p, q, rにより記述される円柱に対する交差
bool IntersectSegmentCylinder(vec3 sa, vec3 sb, vec3 p, vec3 q, float r, out float t)
{
    vec3 d = q - p, m = sa - p, n = sb - sa;
    float md = dot(m, d);
    float nd = dot(n, d);
    float dd = dot(d, d);

    float nn = dot(n, n);
    float mn = dot(m, n);
    float a = dd * nn - nd * nd;
    float k = dot(m, m) - r * r;
    float c = dd * k - md * md;
    float b = dd * mn - nd * md;
    float discr = b * b - a * c;
    if (discr < 0.0) {
      return false; // 実数解がないので交差はない
    }
    t = (-b - sqrt(discr)) / a;
    if (md + t * nd < 0.0) {
       t = -md / nd;
	     // Dot(S(t) - p, S(t) - p) <= r^2 の場合、交差している
       return k + 2.0 * t * (mn + t * nn) <= 0.0;
    } else if (md + t * nd > dd) {
        t = (dd - md) / nd;
	      // Dot(S(t) - q, S(t) - q) <= r^2 の場合、交差している
        return k + dd - 2.0 * md + t * (2.0 * (mn - nd) + t * nn) <= 0.0;
    }
    // 線分が底面の間の間で交差しているので、tは正しい
    return true;
}
bool intCylinder(in vec3 A, in vec3 B, float Radius, in vec3 ro, in vec3 rd, in float tm, out float t ) {
  float lt = 0.0;
  bool r = IntersectSegmentCylinder(ro, ro + rd * 1000.0, A, B, Radius, lt);
  t = lt * 1000.0;
  return r && t < tm;
}

vec3 closest_pt_point_segment(vec3 c, vec3 a, vec3 b, out float t) {
		vec3 ab = b - a;
		t = dot(c - a, ab) * In.dot_ba_ba_inverse;
		t = clamp(t, 0.0, 1.0);
		return a + t * ab;
}


void main (void) {
  vec3 rd = normalize(In.fragViewPos);
  vec3 ro = In.fragViewPos * 0.95;

  float tm = 3000.0;
  float t;

  bool collide = false;
  if(intCylinder(In.p1, In.p2, In.radius, ro, rd, tm, t) ) {
     tm = t;
     collide = true;
  }
  if(intSphere(vec4(In.p1, In.radius), ro, rd, tm, t) ) {
     tm = t;
     collide = true;
  }
  if(intSphere(vec4(In.p2, In.radius), ro, rd, tm, t) ) {
     tm = t;
     collide = true;
  }

  if(collide == false) {
    discard;
  }

  vec3 rPos = ro + rd * tm;

  vec4 pj = u_pmat * vec4(rPos, 1.0);
  float depth = pj.z / pj.w;

  gl_FragDepth = ((gl_DepthRange.diff * depth) + gl_DepthRange.near + gl_DepthRange.far) * 0.5;

  float closest_t;
  vec3 N = normalize(rPos - closest_pt_point_segment(rPos, In.p1, In.p2, closest_t));

  vec3 color = mix(In.color1, In.color2, closest_t);

  // simple lighting
  vec3 L = vec3(0.0, 0.44721359549996, 0.89442719099992);
  float lambert = max(dot(N, L), 0.0);
  float light = lambert * 0.9 + 0.1;
  FragColor = vec4(color * light, 1.0);
}
