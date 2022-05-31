__version__ = '0.11.1+cu102'
git_version = 'fa347eb9f38c1759b73677a11b17335191e3f602'
from torchvision.extension import _check_cuda_version
if _check_cuda_version() > 0:
    cuda = _check_cuda_version()
