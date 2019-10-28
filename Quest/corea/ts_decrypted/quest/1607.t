CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1607;
	title = 160702;

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
				conv = 160709;
				ctype = 1;
				idx = 3172401;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 160708;
				gtype = 0;
				area = 160701;
				goal = 160704;
				grade = 132203;
				rwd = 100;
				sort = 160705;
				stype = 1;
				taid = 1;
				title = 160702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 160707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3172401;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1571;1596;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 160708;
			gtype = 0;
			oklnk = 2;
			area = 160701;
			goal = 160704;
			sort = 160705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 160702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 160714;
			nextlnk = 254;
			rwdtbl = 160701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6203101;
			}
		}
	}
}

