#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
struct TYPE_28__ {int* weaponMidpoint; int /*<<< orphan*/  weaponModel; scalar_t__ barrelModel; } ;
typedef  TYPE_4__ weaponInfo_t ;
typedef  int* vec3_t ;
struct TYPE_29__ {int* origin; int radius; int* shaderRGBA; int** axis; int* oldorigin; int* lightingOrigin; void* nonNormalizedAxes; scalar_t__ hModel; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  shadowPlane; int /*<<< orphan*/  customShader; int /*<<< orphan*/  reType; } ;
typedef  TYPE_5__ refEntity_t ;
struct TYPE_30__ {scalar_t__ giType; scalar_t__ move_type; size_t giTag; } ;
typedef  TYPE_6__ gitem_t ;
struct TYPE_31__ {size_t modelindex; int eFlags; double number; int* angles; } ;
typedef  TYPE_7__ entityState_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_32__ {int /*<<< orphan*/  c1RGBA; } ;
typedef  TYPE_8__ clientInfo_t ;
struct TYPE_33__ {int* lerpOrigin; int* lerpAngles; int miscTime; TYPE_7__ currentState; } ;
typedef  TYPE_9__ centity_t ;
typedef  int /*<<< orphan*/  barrel ;
struct TYPE_27__ {int /*<<< orphan*/  weaponHoverSound; } ;
struct TYPE_25__ {size_t clientNum; } ;
struct TYPE_26__ {TYPE_1__ ps; } ;
struct TYPE_24__ {int time; int* autoAnglesFast; int* autoAngles; TYPE_2__* snap; int /*<<< orphan*/  autoAxis; int /*<<< orphan*/  autoAxisFast; } ;
struct TYPE_23__ {scalar_t__* models; int /*<<< orphan*/  icon; } ;
struct TYPE_22__ {scalar_t__ integer; } ;
struct TYPE_21__ {TYPE_3__ media; TYPE_8__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int*,int**) ; 
 int /*<<< orphan*/  AxisCopy (int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  Byte4Copy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CG_Error (char*,size_t) ; 
 int /*<<< orphan*/  CG_PositionRotatedEntityOnTag (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int EF_NODRAW ; 
 size_t HI_KAMIKAZE ; 
 int ITEM_SCALEUP_TIME ; 
 scalar_t__ IT_ARMOR ; 
 scalar_t__ IT_HEALTH ; 
 scalar_t__ IT_HOLDABLE ; 
 scalar_t__ IT_POWERUP ; 
 scalar_t__ IT_TEAM ; 
 scalar_t__ IT_WEAPON ; 
 scalar_t__ MOVE_TYPE_BOB ; 
 size_t PITCH ; 
 int /*<<< orphan*/  RF_MINLIGHT ; 
 size_t ROLL ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorScale (int*,float,int*) ; 
 size_t WP_RAILGUN ; 
 size_t YAW ; 
 TYPE_6__* bg_itemlist ; 
 size_t bg_numItems ; 
 TYPE_16__ cg ; 
 TYPE_15__* cg_items ; 
 TYPE_14__ cg_simpleItems ; 
 TYPE_4__* cg_weapons ; 
 TYPE_12__ cgs ; 
 int cos (int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_5__*) ; 
 int /*<<< orphan*/  trap_S_AddLoopingSound (double,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CG_Item( centity_t *cent ) {
	refEntity_t		ent;
	entityState_t	*es;
	gitem_t			*item;
	int				msec;
	float			frac;
	float			scale;
	weaponInfo_t	*wi;

	es = &cent->currentState;
	if ( es->modelindex >= bg_numItems ) {
		CG_Error( "Bad item index %i on entity", es->modelindex );
	}

	// if set to invisible, skip
	if ( !es->modelindex || ( es->eFlags & EF_NODRAW ) ) {
		return;
	}

	item = &bg_itemlist[ es->modelindex ];
	if ( cg_simpleItems.integer && item->giType != IT_TEAM ) {
		memset( &ent, 0, sizeof( ent ) );
		ent.reType = RT_SPRITE;
		VectorCopy( cent->lerpOrigin, ent.origin );
		ent.radius = 14;
		ent.customShader = cg_items[es->modelindex].icon;
		ent.shaderRGBA[0] = 255;
		ent.shaderRGBA[1] = 255;
		ent.shaderRGBA[2] = 255;
		ent.shaderRGBA[3] = 255;
		trap_R_AddRefEntityToScene(&ent);
		return;
	}

	memset( &ent, 0, sizeof( ent ) );

	if ( item->move_type == MOVE_TYPE_BOB ) {
		// items bob up and down continuously
		scale = 0.005 + cent->currentState.number * 0.00001;
		cent->lerpOrigin[2] += 4 + cos( ( cg.time + 1000 ) *  scale ) * 4;
		// autorotate at one of two speeds
		if ( item->giType == IT_HEALTH ) {
			VectorCopy( cg.autoAnglesFast, cent->lerpAngles );
			AxisCopy( cg.autoAxisFast, ent.axis );
		} else {
			VectorCopy( cg.autoAngles, cent->lerpAngles );
			AxisCopy( cg.autoAxis, ent.axis );
		}
	} else {
		cent->lerpOrigin[2] += 4;
		AnglesToAxis( es->angles, ent.axis );
	}

	wi = NULL;
	// the weapons have their origin where they attatch to player
	// models, so we need to offset them or they will rotate
	// eccentricly
	if ( item->giType == IT_WEAPON ) {
		wi = &cg_weapons[item->giTag];
		cent->lerpOrigin[0] -= 
			wi->weaponMidpoint[0] * ent.axis[0][0] +
			wi->weaponMidpoint[1] * ent.axis[1][0] +
			wi->weaponMidpoint[2] * ent.axis[2][0];
		cent->lerpOrigin[1] -= 
			wi->weaponMidpoint[0] * ent.axis[0][1] +
			wi->weaponMidpoint[1] * ent.axis[1][1] +
			wi->weaponMidpoint[2] * ent.axis[2][1];
		cent->lerpOrigin[2] -= 
			wi->weaponMidpoint[0] * ent.axis[0][2] +
			wi->weaponMidpoint[1] * ent.axis[1][2] +
			wi->weaponMidpoint[2] * ent.axis[2][2];

		cent->lerpOrigin[2] += 8;	// an extra height boost
	}
	
	if( item->giType == IT_WEAPON && item->giTag == WP_RAILGUN ) {
		clientInfo_t *ci = &cgs.clientinfo[cg.snap->ps.clientNum];
		Byte4Copy( ci->c1RGBA, ent.shaderRGBA );
	}

	ent.hModel = cg_items[es->modelindex].models[0];

	VectorCopy( cent->lerpOrigin, ent.origin);
	VectorCopy( cent->lerpOrigin, ent.oldorigin);

	ent.nonNormalizedAxes = qfalse;

	// if just respawned, slowly scale up
	msec = cg.time - cent->miscTime;
	if ( msec >= 0 && msec < ITEM_SCALEUP_TIME ) {
		frac = (float)msec / ITEM_SCALEUP_TIME;
		VectorScale( ent.axis[0], frac, ent.axis[0] );
		VectorScale( ent.axis[1], frac, ent.axis[1] );
		VectorScale( ent.axis[2], frac, ent.axis[2] );
		ent.nonNormalizedAxes = qtrue;
	} else {
		frac = 1.0;
	}

	// items without glow textures need to keep a minimum light value
	// so they are always visible
	if ( ( item->giType == IT_WEAPON ) ||
		 ( item->giType == IT_ARMOR ) ) {
		ent.renderfx |= RF_MINLIGHT;
	}

	// increase the size of the weapons when they are presented as items
	if ( item->giType == IT_WEAPON ) {
		VectorScale( ent.axis[0], 1.5, ent.axis[0] );
		VectorScale( ent.axis[1], 1.5, ent.axis[1] );
		VectorScale( ent.axis[2], 1.5, ent.axis[2] );
		ent.nonNormalizedAxes = qtrue;
#ifdef MISSIONPACK
		trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, cgs.media.weaponHoverSound );
#endif
	}

#ifdef MISSIONPACK
	if ( item->giType == IT_HOLDABLE && item->giTag == HI_KAMIKAZE ) {
		VectorScale( ent.axis[0], 2, ent.axis[0] );
		VectorScale( ent.axis[1], 2, ent.axis[1] );
		VectorScale( ent.axis[2], 2, ent.axis[2] );
		ent.nonNormalizedAxes = qtrue;
	}
#endif

	// add to refresh list
	trap_R_AddRefEntityToScene(&ent);

	if ( item->giType == IT_WEAPON && wi && wi->barrelModel ) {
		refEntity_t	barrel;
		vec3_t		angles;

		memset( &barrel, 0, sizeof( barrel ) );

		barrel.hModel = wi->barrelModel;

		VectorCopy( ent.lightingOrigin, barrel.lightingOrigin );
		barrel.shadowPlane = ent.shadowPlane;
		barrel.renderfx = ent.renderfx;

		angles[YAW] = 0;
		angles[PITCH] = 0;
		angles[ROLL] = 0;
		AnglesToAxis( angles, barrel.axis );

		CG_PositionRotatedEntityOnTag( &barrel, &ent, wi->weaponModel, "tag_barrel" );

		barrel.nonNormalizedAxes = ent.nonNormalizedAxes;

		trap_R_AddRefEntityToScene( &barrel );
	}

	// accompanying rings / spheres for powerups
	if ( !cg_simpleItems.integer ) 
	{
		vec3_t spinAngles;

		VectorClear( spinAngles );

		if ( item->giType == IT_HEALTH || item->giType == IT_POWERUP )
		{
			if ( ( ent.hModel = cg_items[es->modelindex].models[1] ) != 0 )
			{
				if ( item->giType == IT_POWERUP )
				{
					ent.origin[2] += 12;
					spinAngles[1] = ( cg.time & 1023 ) * 360 / -1024.0f;
				}
				AnglesToAxis( spinAngles, ent.axis );
				
				// scale up if respawning
				if ( frac != 1.0 ) {
					VectorScale( ent.axis[0], frac, ent.axis[0] );
					VectorScale( ent.axis[1], frac, ent.axis[1] );
					VectorScale( ent.axis[2], frac, ent.axis[2] );
					ent.nonNormalizedAxes = qtrue;
				}
				trap_R_AddRefEntityToScene( &ent );
			}
		}
	}
}