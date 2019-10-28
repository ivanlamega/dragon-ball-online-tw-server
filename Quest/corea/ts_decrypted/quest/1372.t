CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1372;
	title = 137202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActItem
			{
				iidx0 = 99035;
				stype0 = 1;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActItem
			{
				iidx0 = 99035;
				stype0 = 1;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = -1;
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				qtidx = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 137214;
			nextlnk = 101;
			rwdtbl = 137201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372206;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 137209;
				ctype = 1;
				idx = 4071109;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 137208;
				m1fx = "1846.000000";
				m2fz = "4759.000000";
				m1fy = "0.000000";
				sort = 137205;
				m2widx = 1;
				grade = 132203;
				m0fx = "1841.000000";
				m0ttip = 137215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 137202;
				gtype = 2;
				area = 137201;
				goal = 137204;
				m0fz = "4762.000000";
				m0widx = 1;
				m1ttip = 137215;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "4760.000000";
				m2fx = "1852.000000";
				m2ttip = 137215;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = 180;
				cnt0 = 4;
				ectype = -1;
				etype = 0;
				qtidx = 137230;
				taid = 3;
				esctype = 0;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137208;
			gtype = 2;
			oklnk = 2;
			area = 137201;
			goal = 137204;
			sort = 137205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071109;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSCheckClrQst
			{
				and = "1369;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 253;
			prelnk = "0;";

			CDboTSActItem
			{
				iidx0 = 99035;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

