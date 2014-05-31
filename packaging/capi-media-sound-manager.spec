Name:       capi-media-sound-manager
Summary:    Sound Manager library
%if 0%{?tizen_profile_mobile}
Version: 0.1.1
Release:    1
%else
Version:    0.1.22
Release:    0
VCS:        framework/api/sound-manager#capi-media-sound-manager_0.1.6-1-29-g1fe3a1eaf827615ba46909f7aaa8f770f88b6a50
%endif
Group:      TO_BE/FILLED_IN
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(mm-sound)
BuildRequires:  pkgconfig(mm-session)
BuildRequires:  pkgconfig(capi-base-common)
%if "%{_repository}" == "wearable"
BuildRequires:  pkgconfig(vconf)
%endif
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A Sound Manager library in Tizen C API

%package devel
Summary:  Sound Manager library (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel
A Sound Manager library in Tizen C API (DEV)

%prep
%setup -q


%build
%if 0%{?tizen_profile_mobile}
cd mobile
%else
cd wearable
%define sec_product_feature_tizenmicro_enable 1

%if 0%{?sec_product_feature_tizenmicro_enable}
        CFLAGS+=" -DTIZEN_MICRO";export CFLAGS
%endif
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%if 0%{?tizen_profile_mobile}
cd mobile
mkdir -p %{buildroot}/usr/share/license
cp LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}
%else
cd wearable
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
%endif


%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%{_libdir}/libcapi-media-sound-manager.so.*
%{_datadir}/license/%{name}
%if 0%{?tizen_profile_mobile}
%manifest mobile/capi-media-sound-manager.manifest
%else
%manifest wearable/capi-media-sound-manager.manifest
%endif

%files devel
%{_includedir}/media/sound_manager.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-media-sound-manager.so


