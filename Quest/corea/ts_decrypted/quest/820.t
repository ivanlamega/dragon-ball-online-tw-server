CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 820;
	title = 82002;

	CNtlTSGroup
	{
		gid = 0;

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
				eitype = 0;
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
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 82007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5062101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 36;
				minlvl = 28;
			}
			CDboTSCheckClrQst
			{
				and = "819;";
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
				conv = 82009;
				ctype = 1;
				idx = 5062101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 82008;
				m1fx = "4879.000000";
				area = 82001;
				goal = 82004;
				m0fz = "622.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 82016;
				sort = 82005;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "683.000000";
				grade = 132203;
				m0fx = "4544.000000";
				m0ttip = 82015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 82002;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 14;
				eitype = 0;
				idx0 = 9612106;
				cnt0 = 14;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5213101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 82014;
			nextlnk = 101;
			rwdtbl = 82001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5062101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 82008;
			gtype = 2;
			oklnk = 2;
			area = 82001;
			goal = 82004;
			sort = 82005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 82002;
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
				itype = 0;
			}
		}
	}
}

