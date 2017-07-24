#pragma once
#ifndef DISTANCE_H
#define DISTANCE_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using std::vector;

struct perFeat //personalized feature 
{
	cv::Mat Sourceimg;
	cv::Rect perFeatRec;
};

enum DISTANCE_TYPE
{
	MANHATTAN,
	EUCLIDEAN,
	COSINE,
	HAMMING,
	COFFICIENT,
	JFFREYSMATUSITA,
	EUCLIDEAN_FUSION
};

#include <cstdlib>
inline unsigned int popcount(unsigned int u)
{
	u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
	u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
	u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
	u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
	u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
	return u;
}

template<typename Dtype>
struct MetricType
{
	static DISTANCE_TYPE distype;

	static Dtype DotProduct(const vector<Dtype>& v1, const vector<Dtype>& v2);
	static Dtype Module(const vector<Dtype>& v);

	// º–Ω«”‡œ“
	static Dtype Cosine(const vector<Dtype>& v1, const vector<Dtype>& v2);

	static Dtype Mean(const vector<Dtype>& v);

	static Dtype Covariance(const vector<Dtype>& v1, const vector<Dtype>& v2);
	// œ‡πÿœµ ˝
	static Dtype CorrelationCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// DiceCoefficient œµ ˝
	static Dtype DiceCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// JaccardCoefficient œµ ˝
	static Dtype JaccardCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// Minkowsky æ‡¿Î
	static Dtype MinkowskyDistance(const vector<Dtype>& v1, const vector<Dtype>& v2, Dtype m);

	// Euclidean æ‡¿Î
	static Dtype EuclideanDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

	static Dtype EuclideanDistanceFusion(const vector<Dtype>& v1, const vector<Dtype>& v2, int class_num);

	// Manhattan æ‡¿Î
	static Dtype ManhattanDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// Jffreys & Matusita æ‡¿Î
	static Dtype JffreysMatusitaDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// Mahalanobis æ‡¿Î
	static Dtype MahalanobisDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// Camberra æ‡¿Î£®Lance æ‡¿Î£¨Williams æ‡¿Î£©
	static Dtype CamberraDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

	// hamming æ‡¿Î
	static int HammingDistance(const vector<Dtype>& v1, const vector<Dtype>& v2);

};

template<typename Dtype>
Dtype MetricType<Dtype>::DotProduct(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += v1[i] * v2[i];
	}
	return ret;
}

template<typename Dtype>
Dtype MetricType<Dtype>::Module(const vector<Dtype>& v)
{
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v.size(); ++i)
	{
		ret += v[i] * v[i];
	}
	return sqrt(ret);
}

template<typename Dtype>
Dtype MetricType<Dtype>::Cosine(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return DotProduct(v1, v2) / (Module(v1) * Module(v2));
}

template<typename Dtype>
Dtype MetricType<Dtype>::Mean(const vector<Dtype>& v)
{
	assert(v.size() != 0);
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v.size(); ++i)
	{
		ret += v[i];
	}
	return ret / v.size();
}

template<typename Dtype>
Dtype MetricType<Dtype>::Covariance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size() && v1.size() > 1);
	Dtype ret = 0.0;
	Dtype v1a = Mean(v1), v2a = Mean(v2);

	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += (v1[i] - v1a) * (v2[i] - v2a);
	}
	return ret / (v1.size() - 1);
}

// œ‡πÿœµ ˝
template<typename Dtype>
Dtype MetricType<Dtype>::CorrelationCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return Covariance(v1, v2) / sqrt(Covariance(v1, v1) * Covariance(v2, v2));
}

// DiceCoefficient œµ ˝
template<typename Dtype>
Dtype MetricType<Dtype>::DiceCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return 2.0 * DotProduct(v1, v2) / (DotProduct(v1, v1) + DotProduct(v2, v2));
}

// JaccardCoefficient œµ ˝
template<typename Dtype>
Dtype MetricType<Dtype>::JaccardCoefficient(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return DotProduct(v1, v2) / (DotProduct(v1, v2) + DotProduct(v2, v2) - DotProduct(v1, v2));
}

// MinkowskyDistance æ‡¿Î
template<typename Dtype>
Dtype MetricType<Dtype>::MinkowskyDistance(const vector<Dtype>& v1, const vector<Dtype>& v2, Dtype m)
{
	assert(v1.size() == v2.size());
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += pow(abs(v1[i] - v2[i]), m);
	}
	return pow(ret, 1.0 / m); // vs2012
							  // return pow(float(ret), float(1.0 / m)); // vs2010b÷ÿ‘ÿŒﬁ∑®≈–±
}

// EuclideanDistance æ‡¿Î
template<typename Dtype>
Dtype MetricType<Dtype>::EuclideanDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return MinkowskyDistance(v1, v2, 2.0);
}


template<typename Dtype>
Dtype MetricType<Dtype>::EuclideanDistanceFusion(const vector<Dtype>& v1, const vector<Dtype>& v2, int class_num)
{
	int feat_dim = v1.size();
	vector<Dtype> v1_prob(class_num);
	vector<Dtype> v2_prob(class_num);
	vector<Dtype> v1_feat(feat_dim - class_num);
	vector<Dtype> v2_feat(feat_dim - class_num);
	for (int i = 0; i < feat_dim - class_num; i++)
	{
		v1_feat[i] = v1[i];
		v2_feat[i] = v2[i];
	}

	for (int i = 0; i < class_num; i++)
	{
		v1_prob[i] = v1[feat_dim - class_num + i];
		v2_prob[i] = v2[feat_dim - class_num + i];
	}
	Dtype weight = DotProduct(v1_prob, v2_prob);
	assert(v1_feat.size() == v2_feat.size());
	return MinkowskyDistance(v1_feat, v2_feat, 2.0) / static_cast<float>(weight);
}


// ManhattanDistance æ‡¿Î
template<typename Dtype>
Dtype MetricType<Dtype>::ManhattanDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return MinkowskyDistance(v1, v2, 1.0);
}

// Jffreys & Matusita æ‡¿Î
template<typename Dtype>
Dtype MetricType<Dtype>::JffreysMatusitaDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += (sqrt(v1[i]) - sqrt(v2[i])) * (sqrt(v1[i]) - sqrt(v2[i]));
	}
	return sqrt(ret);
}

// MahalanobisDistance æ‡¿Î
template<typename Dtype>
Dtype MetricType<Dtype>::MahalanobisDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	return 0.0;
}

// CamberraDistance æ‡¿Î£®Lance æ‡¿Î£¨Williams æ‡¿Î£©
template<typename Dtype>
Dtype MetricType<Dtype>::CamberraDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	assert(v1.size() == v2.size());
	Dtype ret = 0.0;
	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += abs(v1[i] - v2[i]) / abs(v1[i] + v2[i]);
	}
	return ret;
}

template<typename Dtype>
int MetricType<Dtype>::HammingDistance(const vector<Dtype>& v1, const vector<Dtype>& v2)
{
	int dist = 0;
	for (vector<Dtype>::size_type i = 0; i != v1.size(); ++i)
	{
		dist += popcount(static_cast<uint32_t>(v1[i]) ^ static_cast<uint32_t>(v2[i]));
	}
	return dist;
}

#endif // !DISTANCE_H

