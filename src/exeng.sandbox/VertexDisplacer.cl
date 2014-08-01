
__kernel void VertexDisplacer(__global float *value, float displace) {
	const int i = get_global_id(0);
	if (i%3 != 2) {
		value[i] += displace;
	}
}
