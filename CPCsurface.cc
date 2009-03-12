#include "CPCsurface.hh"

/*
a = 0.04; (* m *)
g = 9.80665; (* m/s^2 *)
m = 10.454077; (* neV s^2/m^2 *)
mg = m g;
\epsilon = 10E-8;
//imagescalar = 2000;
bool verbose = false;
tsum = 0;
count = 0;
BigEnough[x_] := Return[Abs[x] > \epsilon];
*/

//IntersectCPC[PathState[{r_, z_}, {vr_, vphi_, vz_}]] := 
double intersectCPC(PathState* pathstate)
//double CPCsurface::intersect(PathState* pathstate)
{
	double vphi = pathstate->getAngularVelocity();
	//double gm = g + (vr^2 + vphi^2)/(2a);
	double gm = g + (vr*vr + vphi*vphi)/(2a);
	double vzm = vz - (vr*r)/(2*a);
	//double zm = z + (3*a^2 - r^2)/(4*a);
	double zm = z + (3*a*a - r*r)/(4*a);
	double tr2 = 2*r/gm; 
	double tz2 = 2*zm/gm;
	double tr = sqrt(tr2);
	double tz = sqrt(tz2);
	double tvr = vr/gm; 
	double tvphi = vphi/gm; 
	double tvz = vzm/gm;

	// b = -4 tvz;
	// c = 4 tvz^2 - tvphi^2 - tvr^2 - 2tz^2;
	// d = 4 tvz tz^2 - tvr tr^2;
	// e = tz^4 - 1/4 tr^4;
	double b = -4*tvz;
	double c = 4*tvz*tvz - tvphi*tvphi - tvr*tvr - 2*tz*tz;
	double d = 4*tvz*tz2 - tvr*tr2;
	double e = tz2*tz2 - 1/4 tr2*tr2;

	double b2 = b*b;
	double alpha = -3/8*b2 + c;
	double beta = 1/8*b2*b - 1/2*b*c + d;
	double gamma = -3/256*b2*b2 + 1/16*b2*c - 1/4*b*d + e;
	if(beta == 0) return -1;
	// P = -1/12*alpha^2 - gamma;
	// Q = -1/108*alpha^3 + 1/3 alpha gamma - 1/8 beta^2;
	P = -1/12*alpha*alpha - gamma;
	Q = -1/108*alpha*alpha*alpha + 1/3*alpha*gamma - 1/8*beta*beta;
	//upsilon = Power[1/2*Q + Sqrt[1/4*Q^2+1/27*P^3], (3)^-1];
	double upsilon = pow(1/2*Q + Sqrt[1/4*Q*Q + 1/27*P*P*P], 1/3);
	double psi = -5/6*alpha - upsilon;
	if(upsilon != 0)
		psi += P/(3*upsilon);
	double omega = sqrt(alpha + 2*psi);
	double zeta = 3*alpha + 2*psi;
	double xi = (2*beta)/omega;
	double roots[] = {
		tvz + (omega + Sqrt[-zeta-xi])/2, 
		tvz + (omega - Sqrt[-zeta-xi])/2, 
		tvz - (omega - Sqrt[-zeta+xi])/2, 
		tvz - (omega + Sqrt[-zeta+xi])/2
	};
	//if(verbose, Print["all roots = ", roots]];
	positiveroots = Select[roots, Positive[#] &];
	//if(verbose, Print["positive roots = ", positiveroots]];
	t = Min[positiveroots];
	if(t < epsilon) 
		Print["error, some how we have a small one ", t];
	if(verbose)
		Print["returning root = ",t];
	return t;
	/*{roots,Solve[x^4 + b x^3 + c x^2 + d x + e == 0, x]}*/
}

/*
UCNPath2D[t_, PathState[{r_, z_}, {vr_, vphi_, vz_}]] := 
	{Sqrt[vphi^2 t^2 + (vr t + r)^2], -1/2g t^2 + vz t + z}

UCNVelocity2D[t_, PathState[{r_, z_}, {vr_, vphi_, vz_}]] := 
Module[{l, rnew, vrnew, vphinew, vznew},
	l = r vphi; (* constant of motion *)
	rnew = Sqrt[vphi^2 t^2 + (vr t + r)^2];
	vrnew = ((vr^2 + vphi^2)t + vr r)/rnew;
	vphinew = l/rnew;
	vznew = -g t + vz;
	{vrnew, vphinew, vznew}
]

UCNPathState[t_, PathState[{r_, z_}, {vr_, vphi_, vz_}]] := 
Module[{pathstate = PathState[{r, z}, {vr, vphi, vz}]},
	PathState[UCNPath2D[t, pathstate], UCNVelocity2D[t, pathstate]]
]
UCNMaximumHeight[PathState[{r_, z_}, {vr_, vphi_, vz_}]] := (vr^2 + vphi^2 + vz^2)/(2g) + z
UCNPathApogee[PathState[{r_, z_}, {vr_, vphi_, vz_}]] := vz^2/(2g) + z

UCNMaximumHeightTime[PathState[{r_, z_}, {vr_, vphi_, vz_}]] := Sqrt[vr^2 + vphi^2 + vz^2]/g

UCNPathApogeeTime[PathState[{r_, z_}, {vr_, vphi_, vz_}]] := vz/g

UCNBalisticBound[r_, h_] := -1/(4h)(r + a)^2 + h;

PlotUCNPath2D[PathState[{r_, z_}, {vr_, vphi_, vz_}], {tmin_, tmax_}] :=
	ParametricPlot[UCNPath2D[t, PathState[{r, z}, {vr, vphi, vz}]], {t, tmin, tmax}];

CPCWallHeight[r_] := 1/(4a) (r + a)^2 - a
CPCWallRadius[h_] := -a + 2Sqrt[a^2+ a h]

CPCWallNormal2D[{r_, z_}] := {-r-a, 2a}/Sqrt[r^2 + 2a r + 5a^2]

CPCWallNormal3D[{r_, z_}] := {-r-a, 0, 2a}/Sqrt[r^2 + 2a r + 5a^2]

ReflectCPCPath2D[t_, PathState[{r_, z_}, {vr_, vphi_, vz_}], {nr_, nphi_, nz_}] := 
Module[{x,v},	
	x = UCNPath2D[t, PathState[{r, z}, {vr, vphi, vz}]];
	v = UCNVelocity2D[t, PathState[{r, z}, {vr, vphi, vz}]] - 2({vr,vphi,vz}.{nr,nphi,nz}){nr,nphi,nz};
	PathState[x, v]
]

ReflectCPCPath2D[t_, PathState[{r_, z_}, {vr_, vphi_, vz_}]] := 
Module[{pathstate,x,n,v,vnew},
	pathstate = PathState[{r, z}, {vr, vphi, vz}];
	x = UCNPath2D[t, pathstate];
	n = CPCWallNormal3D[x];
	v = UCNVelocity2D[t, pathstate];
	vnew = v - 2(v.n)n;
	PathState[x, vnew]
]

PlotCPCWall2D[h_] := Show[
	ParametricPlot[{r, CPCWallHeight[r]}, {r, a, CPCWallRadius[h+a]}, 
						PlotRange->{{0, CPCWallRadius[h+a]}, {0, h+a}},
						PlotStyle->{Thick, Black}],
	(*Plot[h-a,{r,0,CPCWallRadius[h-a]},PlotStyle->{Dashed,Black}],*)
	Plot[UCNBalisticBound[r, h], {r,0,CPCWallRadius[h-a]}, PlotStyle->{Dashed,Black}],
	Plot[h,{r,0,CPCWallRadius[h]},PlotStyle->{Dashed,Black}]
]
*/
