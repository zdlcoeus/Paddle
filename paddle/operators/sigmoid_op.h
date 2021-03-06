/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#pragma once

#include "paddle/operators/type_alias.h"

namespace paddle {
namespace operators {

template <typename Place, typename T>
class SigmoidKernel : public OpKernel {
public:
  void Compute(const ExecutionContext& context) const override {
    auto input = context.Input<Tensor>(0);
    auto output = context.Output<Tensor>(0);
    output->mutable_data<T>(context.GetPlace());

    EigenVector<T>::Flatten(*output).device(
        *(context.GetEigenDevice<Place>())) =
        1.0 / (1.0 + (-1.0 * EigenVector<T>::Flatten(*input)).exp());
  }
};
}  // namespace operators
}  // namespace paddle
