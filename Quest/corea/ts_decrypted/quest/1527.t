CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1527;
	title = 152702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 152709;
				ctype = 1;
				idx = 3242201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 152708;
				gtype = 0;
				area = 152701;
				goal = 152704;
				grade = 132203;
				rwd = 100;
				sort = 152705;
				stype = 1;
				taid = 1;
				title = 152702;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 152708;
			gtype = 0;
			oklnk = 2;
			area = 152701;
			goal = 152704;
			sort = 152705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 152702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 152714;
			nextlnk = 254;
			rwdtbl = 152701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801110;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 152707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3242201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1514;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
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
}

