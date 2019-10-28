CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6036;
	title = 603602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 603607;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6010;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 603609;
				ctype = 1;
				idx = 4141101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 603608;
				gtype = 1;
				area = 603601;
				goal = 603604;
				grade = -1;
				rwd = 100;
				sort = 603605;
				stype = 8;
				taid = 1;
				title = 603602;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 603608;
			gtype = 1;
			oklnk = 2;
			area = 603601;
			goal = 603604;
			sort = 603605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 603614;
			nextlnk = 253;
			rwdtbl = 603601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372203;
			}
		}
	}
}

