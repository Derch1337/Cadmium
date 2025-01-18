#pragma once
#include "../Math/Math.h"
#include <vector>

struct BonePosition {
	float x;
	char padding1[0xC];
	float y;
	char padding2[0xC];
	float z;
	char padding3[0xC];
};


struct BoneMemoryPage
{
	BonePosition Page[32];
};



struct BoneGroupData
{
	Vector3 WorldPosition;
	Vector2 ScreenPosition;
	bool IsVisible;
};

struct hitbox_t
{
	Vector3 bMin;
	Vector3 bMax;
	int bone;
};

const BoneID BonePair[20][2] = {
		{HEAD, FACE},
		{FACE, NECK},

		{NECK, RIGHT_NECK},
		{RIGHT_NECK, RIGHT_SHOULDER},
		{RIGHT_SHOULDER, RIGHT_ELBOW},
		{RIGHT_ELBOW, RIGHT_HAND},

		{NECK, LEFT_NECK},
		{LEFT_NECK, LEFT_SHOULDER},
		{LEFT_SHOULDER, LEFT_ELBOW},
		{LEFT_ELBOW, LEFT_HAND},

		{NECK, CHEST},
		{CHEST, BODY},
		{BODY, STOMACH},
		{STOMACH, PELVIS},

		{PELVIS, LEFT_HIPS},
		{LEFT_HIPS, LEFT_KNEE},
		{LEFT_KNEE, LEFT_ANKLE},

		{PELVIS, RIGHT_HIPS},
		{RIGHT_HIPS, RIGHT_KNEE},
		{RIGHT_KNEE, RIGHT_ANKLE},
};

/// <summary>
/// use "VectorTransform" and the bonematrix to get the player's hitboxes 
/// you can use this form hitbox - aimbot, or a triggerbot, that works on all servers
/// </summary>

const std::vector<hitbox_t> HitBoxArray = {
	{Vector3(-8.299200f, -7.727200f, -5.428800f), Vector3(8.299200f, 2.007200f, 6.583200f), 0},
	{Vector3(4.576000f, -5.376800f, -3.432000f),  Vector3(22.879999f, 3.775200f, 4.576000f), 1},
	{Vector3(-0.291200f, -4.295200f, -3.432000f), Vector3(20.883200f, 3.151200f, 3.432000f), 2},
	{Vector3(-2.288000f, -1.144000f, -2.579200f), Vector3(5.720000f, 4.576000f, 2.007200f), 3},
	{Vector3(-2.860000f, -2.808000f, -2.860000f), Vector3(4.004000f, 1.196000f, 1.716000f), 4},
	{Vector3(4.576000f, -5.376800f, -3.432000f),  Vector3(22.879999f, 3.775200f, 4.576000f), 5},
	{Vector3(-0.291200f, -4.295200f, -3.432000f), Vector3(20.883200f, 3.151200f, 3.432000f), 6},
	{Vector3(-2.288000f, -1.144000f, -2.007200f), Vector3(5.720000f, 4.576000f, 2.579200f), 7},
	{Vector3(-2.860000f, -2.808000f, -1.716000f), Vector3(4.004000f, 1.196000f, 2.860000f), 8},
	{Vector3(-9.151999f, -1.258400f, -8.007999f), Vector3(4.576000f, 11.325600f, 8.007999f), 10},
	{Vector3(-3.068000f, -3.432000f, -9.692800f), Vector3(13.572000f, 10.316800f, 9.692800f), 11},
	{Vector3(-0.104000f, -4.576000f, -2.860000f), Vector3(5.512000f, 2.288000f, 2.860000f), 13},
	{Vector3(-0.416000f, -6.240000f, -3.640000f), Vector3(9.360000f, 4.440800f, 3.016000f), 14},
	{Vector3(-1.144000f, -2.579200f, -2.288000f), Vector3(14.872000f, 2.579200f, 2.288000f), 16},
	{Vector3(-1.716000f, -2.402400f, -2.402400f), Vector3(13.155999f, 2.402400f, 2.402400f), 17},
	{Vector3(0.291200f, -2.464800f, -1.716000f),  Vector3(6.583200f, 1.549600f, 2.860000f), 18},
	{Vector3(-1.144000f, -2.579200f, -2.288000f), Vector3(14.872000f, 2.579200f, 2.288000f), 29},
	{Vector3(-1.716000f, -2.402400f, -2.402400f), Vector3(13.155999f, 2.402400f, 2.402400f), 30},
	{Vector3(0.291200f, -2.464800f, -2.860000f),  Vector3(6.583200f, 1.549600f, 1.716000f), 31}
};