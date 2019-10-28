CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 896;
	title = 89602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 89607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3332101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "895;";
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
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
				conv = 89609;
				ctype = 1;
				idx = 3332101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 89608;
				m1fx = "5421.000000";
				m2fz = "844.000000";
				m1fy = "0.000000";
				sort = 89605;
				m2widx = 1;
				grade = 132203;
				m0fx = "5686.000000";
				m0ttip = 89615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 89602;
				gtype = 0;
				area = 89601;
				goal = 89604;
				m0fz = "1112.000000";
				m0widx = 1;
				m1ttip = 89616;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "579.000000";
				m2fx = "6361.000000";
				m2ttip = 89617;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 1069;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 89608;
			gtype = 0;
			oklnk = 2;
			area = 89601;
			goal = 89604;
			sort = 89605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 89602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 89614;
			nextlnk = 101;
			rwdtbl = 89601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3332101;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 16;
				iidx = 1069;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
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

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1069;
				taid = 1;
				type = 1;
			}
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

