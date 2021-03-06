#include "caffe2/operators/filler_op.h"

namespace caffe2 {

template <>
bool RangeFillOp<float, CPUContext>::Fill(
    TensorCPU* output) {
  float* data = output->mutable_data<float>();
  for (int i = 0; i < output->size(); ++i) {
    data[i] = i;
  }
  return true;
}

namespace {

REGISTER_CPU_OPERATOR(UniformFill, UniformFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(UniformIntFill, UniformFillOp<int, CPUContext>);
REGISTER_CPU_OPERATOR(ConstantFill, ConstantFillOp<CPUContext>);
REGISTER_CPU_OPERATOR(GivenTensorFill, GivenTensorFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(GivenTensorIntFill, GivenTensorFillOp<int, CPUContext>);
REGISTER_CPU_OPERATOR(
    GivenTensorInt64Fill,
    GivenTensorFillOp<int64_t, CPUContext>);
REGISTER_CPU_OPERATOR(
    GivenTensorStringFill,
    GivenTensorFillOp<std::string, CPUContext>);
REGISTER_CPU_OPERATOR(GaussianFill, GaussianFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(XavierFill, XavierFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(MSRAFill, MSRAFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(RangeFill, RangeFillOp<float, CPUContext>);
REGISTER_CPU_OPERATOR(LengthsRangeFill, LengthsRangeFillOp<CPUContext>);


std::vector<TensorShape> FillerTensorInference(
    const OperatorDef& def,
    const vector<TensorShape>& in) {
      vector<TensorShape> out(1);
      ArgumentHelper helper(def);
      out[0].set_data_type(static_cast<TensorProto_DataType>(
          helper.GetSingleArgument<int>(
            "dtype",
            TensorProto_DataType_FLOAT)
          )
      );

      if (in.size()) {
        // TODO
        bool input_as_shape =
          helper.GetSingleArgument<bool>("input_as_shape", false);
        if (input_as_shape) {
          out[0].set_unknown_shape(true);
          return out;
        }
        for (int d : in[0].dims()) {
          out[0].add_dims(d);
        }
      } else {
        auto shape = helper.GetRepeatedArgument<int>("shape");
        for (int d : shape) {
          out[0].add_dims(d);
        }
      }
      return out;
}

OPERATOR_SCHEMA(ConstantFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference)
    .SetDoc(R"DOC(
The operator fills the elements of the output tensor with a constant value
specified by the 'value' argument.

The data type is specified by the 'dtype' argument. The 'dtype' argument must
be one of the data types specified in the 'DataType' enum field in the
TensorProto message. If the 'dtype' argument is not provided, the data type of
'value' is used.

The output tensor shape is specified by the 'shape' argument. If the number of
input is 1, the shape will be identical to that of the input at run time with
optional additional dimensions appended at the end as specified by 'extra_shape'
argument. In that case the 'shape' argument should not be set.

If input_as_shape is set to true, then the input should be a 1D tensor
containing the desired output shape (the dimensions specified in extra_shape
will also be appended)

NOTE: Currently, it supports data type of float, int32, int64, and bool.
)DOC")
    .Arg("value", "The value for the elements of the output tensor.")
    .Arg(
        "dtype",
        "The data type for the elements of the output tensor."
        "Strictly must be one of the types from DataType enum in TensorProto.")
    .Arg(
        "shape",
        "The shape of the output tensor."
        "Cannot set the shape argument and pass in an input at the same time.")
    .Arg(
        "extra_shape",
        "The additional dimensions appended at the end of the shape indicated"
        "by the input blob."
        "Cannot set the extra_shape argument when there is no input blob.")
    .Arg("input_as_shape", "1D tensor containing the desired output shape")
    .Input(0, "input", "Input tensor (optional) to provide shape information.")
    .Output(
        0,
        "output",
        "Output tensor of constant values specified by 'value'"
        "argument and its type is specified by the 'dtype' argument");


OPERATOR_SCHEMA(UniformFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);

OPERATOR_SCHEMA(UniformIntFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(GivenTensorFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(GivenTensorIntFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(GivenTensorInt64Fill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(GivenTensorStringFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(GaussianFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(XavierFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(MSRAFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);
OPERATOR_SCHEMA(RangeFill)
    .NumInputs(0, 1)
    .NumOutputs(1)
    .AllowInplace({{0, 0}})
    .TensorInferenceFunction(FillerTensorInference);

NO_GRADIENT(UniformFill);
NO_GRADIENT(UniformIntFill);
NO_GRADIENT(ConstantFill);
NO_GRADIENT(GivenTensorFill);
NO_GRADIENT(GivenTensorIntFill);
NO_GRADIENT(GivenTensorInt64Fill);
NO_GRADIENT(GaussianFill);
NO_GRADIENT(XavierFill);
NO_GRADIENT(MSRAFill);
NO_GRADIENT(RangeFill);

OPERATOR_SCHEMA(LengthsRangeFill)
    .NumInputs(1)
    .NumOutputs(1)
    .SetDoc(R"DOC(
Convert a length vector to a range sequene. For example, input=[4,3,1], the
output would be [0,1,2,3,0,1,2,0].
)DOC")
    .Input(0, "lengths", "1D tensor of int32 or int64 segment lengths.")
    .Output(
        0,
        "range_sequence",
        "1D tensor whose size is the sum of `lengths`");
NO_GRADIENT(LengthsRangeFill);

}  // namespace
}  // namespace caffe2
